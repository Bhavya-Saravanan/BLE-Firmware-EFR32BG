/***********************************************************************
 * @file      i2c.h
 * @version   1.0
 * @brief     Header file for I2C communication with Si7021 temperature sensor.
 *
 * @author    Bhavya Saravanan, bhsa3618@colorado.edu
 * @date      13-02-2025
 *
 * @institution University of Colorado Boulder (UCB)
 * @course      ECEN 5823: IoT Embedded Firmware
 * @instructor  Chris Choi
 *
 * @resources  Lecture slides
 ***********************************************************************/


#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
#include <stdbool.h>
#include "em_i2c.h"

/**
 * @brief Initializes the I2C interface.
 * @param None
 * @return None
 */
void i2c_init(void);

/**
 * @brief Powers the Si7021 temperature sensor ON/OFF.
 * @param enable Boolean flag to turn sensor power ON (true) or OFF (false).
 * @return None
 */
void tsl2561_enable(void);

/**
 * @brief Sends a temperature measurement command to the Si7021 sensor.
 * @param None
 * @return None
 */
void tsl2561_read_channels(void);

/**
 * @brief Reads temperature data from the Si7021 sensor.
 * @param None
 * @return None
 */
uint16_t tsl2561_calculate_lux(void);

/**
 * @brief Processes the temperature reading and converts it to Celsius.
 * @param None
 * @return None
 */
void I2C0_IRQHandler(void);

/**
 * @brief I2C interrupt handler.
 * @param None
 * @return temperature value after the calculated formula for the celsius value
 */


#endif /* I2C_H_ */

