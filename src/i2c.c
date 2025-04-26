/***********************************************************************
 * @file      i2c.c
 * @version   1.0
 * @brief      Implementation file for I2C communication with Si7021 temperature sensor.
 *
 * @author    Bhavya Saravanan, bhsa3618@colorado.edu
 * @date      20-02-2025
 *
 * @institution University of Colorado Boulder (UCB)
 * @course      ECEN 5823: IoT Embedded Firmware
 * @instructor  Chris Choi
 *
 * @resources  Lecture slides
 ***********************************************************************/

#include "i2c.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_i2c.h"
#include "sl_i2cspm.h"
#include "src/timer.h"
#include "src/oscillator.h"
#include "src/scheduler.h"
#include "src/i2c.h"

#define INCLUDE_LOG_DEBUG 1
#include "src/log.h"
#include "em_i2c.h"
#include "em_gpio.h"
#include "sl_i2cspm.h"
#include "src/timer.h"
/***************************************************************************//**
 * @file i2c.c
 * @brief I2C driver for TSL2561 light sensor (for Blue Gecko EFR32BG13)
 ******************************************************************************/

#include "i2c.h"
#include "em_i2c.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "src/log.h"
#include "src/scheduler.h"
#include "src/timer.h"

#define INCLUDE_LOG_DEBUG 1

// I2C Configuration for EFR32BG13
#define I2C_SCL_PORT    gpioPortC
#define I2C_SCL_PIN     10
#define I2C_SDA_PORT    gpioPortC
#define I2C_SDA_PIN     11

// TSL2561 I2C Address
#define TSL2561_ADDR            (0x39)

// TSL2561 Registers
#define TSL2561_CMD_BIT         (0x80)  // Command bit
#define TSL2561_REG_CONTROL     (0x00)
#define TSL2561_REG_TIMING      (0x01)
#define TSL2561_REG_DATA0LOW    (0x0C)
#define TSL2561_REG_DATA0HIGH   (0x0D)
#define TSL2561_REG_DATA1LOW    (0x0E)
#define TSL2561_REG_DATA1HIGH   (0x0F)

// Control Register Commands
#define TSL2561_POWER_ON         (0x03)
#define TSL2561_POWER_OFF        (0x00)

// Global Variables
static I2C_TransferSeq_TypeDef i2cTransfer;
static uint8_t i2c_data_buffer[4];    // For reading CH0 and CH1
static volatile bool transferInProgress = false;

// Raw channel data
static uint16_t ch0 = 0;
static uint16_t ch1 = 0;

/*******************************************************************************
 * Function: i2c_init
 * Initializes the I2C0 peripheral.
 ******************************************************************************/
void i2c_init(void)
{
    // Enable clocks
    CMU_ClockEnable(cmuClock_GPIO, true);
    CMU_ClockEnable(cmuClock_I2C0, true);

    // Configure GPIO for I2C
    GPIO_PinModeSet(I2C_SCL_PORT, I2C_SCL_PIN, gpioModeWiredAndPullUp, 1);
    GPIO_PinModeSet(I2C_SDA_PORT, I2C_SDA_PIN, gpioModeWiredAndPullUp, 1);

    // Route location (optional based on board config)
    I2C0->ROUTELOC0 = (I2C_ROUTELOC0_SCLLOC_LOC14 | I2C_ROUTELOC0_SDALOC_LOC16);
    I2C0->ROUTEPEN  = (I2C_ROUTEPEN_SCLPEN | I2C_ROUTEPEN_SDAPEN);

    // Initialize I2C
    I2C_Init_TypeDef i2cInit = I2C_INIT_DEFAULT;
    I2C_Init(I2C0, &i2cInit);

    // Abort previous transfers
    if (I2C0->STATE & I2C_STATE_BUSY) {
        I2C0->CMD = I2C_CMD_ABORT;
    }
}

/*******************************************************************************
 * Function: tsl2561_enable
 * Enables the TSL2561 sensor by writing to CONTROL register.
 ******************************************************************************/
void tsl2561_enable(void)
{
    uint8_t tx_buffer[2];
    tx_buffer[0] = TSL2561_CMD_BIT | TSL2561_REG_CONTROL;   // Command + CONTROL register
    tx_buffer[1] = TSL2561_POWER_ON;                        // Power ON

    i2cTransfer.addr = TSL2561_ADDR << 1;
    i2cTransfer.flags = I2C_FLAG_WRITE;
    i2cTransfer.buf[0].data = tx_buffer;
    i2cTransfer.buf[0].len = 2;

    transferInProgress = true;

    NVIC_ClearPendingIRQ(I2C0_IRQn);
    NVIC_EnableIRQ(I2C0_IRQn);

    if (I2C_TransferInit(I2C0, &i2cTransfer) != i2cTransferInProgress) {
        LOG_ERROR("I2C Write Failed: TSL2561 Enable");
    }
}

/*******************************************************************************
 * Function: tsl2561_read_channels
 * Reads 4 bytes: CH0 low, CH0 high, CH1 low, CH1 high.
 ******************************************************************************/
void tsl2561_read_channels(void)
{
    static uint8_t reg = TSL2561_CMD_BIT | TSL2561_REG_DATA0LOW;

    i2cTransfer.addr = TSL2561_ADDR << 1;
    i2cTransfer.flags = I2C_FLAG_WRITE_READ;
    i2cTransfer.buf[0].data = &reg;
    i2cTransfer.buf[0].len = 1;
    i2cTransfer.buf[1].data = i2c_data_buffer;
    i2cTransfer.buf[1].len = 4;

    transferInProgress = true;

    NVIC_ClearPendingIRQ(I2C0_IRQn);
    NVIC_EnableIRQ(I2C0_IRQn);

    if (I2C_TransferInit(I2C0, &i2cTransfer) != i2cTransferInProgress) {
        LOG_ERROR("I2C Read Failed: TSL2561 Read Channels");
    }
}

/*******************************************************************************
 * Function: tsl2561_calculate_lux
 * Calculates lux value from CH0 and CH1.
 ******************************************************************************/
uint16_t tsl2561_calculate_lux(void)
{
    ch0 = (i2c_data_buffer[1] << 8) | i2c_data_buffer[0];   // CH0 = high byte << 8 + low byte
    ch1 = (i2c_data_buffer[3] << 8) | i2c_data_buffer[2];   // CH1 = high byte << 8 + low byte

    if (ch0 == 0) return 0; // Avoid division by zero

    uint32_t ratio = (ch1 << 10) / ch0; // (ch1/ch0) * 1024
    uint32_t lux = 0;

    if (ratio <= 500) lux = (0x01f4 * ch0 - 0x01f4 * ch1) >> 10;
    else if (ratio <= 610) lux = (0x0204 * ch0 - 0x0282 * ch1) >> 10;
    else if (ratio <= 800) lux = (0x01d1 * ch0 - 0x0363 * ch1) >> 10;
    else lux = 0;

    return (uint16_t)lux;
}

/*******************************************************************************
 * Function: I2C0_IRQHandler
 * Handles I2C interrupts (transfer complete).
 ******************************************************************************/
void I2C0_IRQHandler(void)
{
    I2C_TransferReturn_TypeDef status;

    status = I2C_Transfer(I2C0);

    if (status == i2cTransferDone)
    {
        transferInProgress = false;
        schedulerSetEventI2CComplete(); // Signal to BLE that I2C is done
    }
    else if (status < 0)
    {
        LOG_ERROR("I2C Error: Status = %d", status);
        transferInProgress = false;
    }
}
