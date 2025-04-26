/***********************************************************************
 * @file      scheduler.h
 * @version   1.0
 * @brief     Header file for scheduler event management.
 *
 * @author    Bhavya Saravanan, bhsa3618@colorado.edu
 * @date      13-03-2025
 *
 * @institution University of Colorado Boulder (UCB)
 * @course      ECEN 5823: IoT Embedded Firmware
 * @instructor  Chris Choi
 *
 * @resources  Prerecorder schedulers video
 ***********************************************************************/


#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stdint.h>
#include "sl_bt_api.h"

// Define external signals used with `sl_bt_external_signal()`
#define LIGHT_EVENT    (1 << 0)  // External signal for temperature event
#define TIMER_EVENT          (1 << 1)  // External signal for timer expiration
#define I2C_EVENT            (1 << 2)  // External signal for I2C transfer complete



#define PB0_EVENT            (1<<4)   // External signal foe pb0 pressed
#define PB0_RELEASED          (1<<6)  // External signal for pb0 released

// Define the 16-bit UUIDs (in little-endian)

#define HEALTH_THERMOMETER_SERVICE_UUID  0x1809
#define TEMPERATURE_MEASUREMENT_CHAR_UUID 0x2A1C

typedef enum {
    SCANNING,                // Searching for the server & connecting
    DISCOVER_SERVICE,        // Discovering the Health Thermometer Service (0x1809)
    DISCOVER_CHARACTERISTIC, // Discovering the Temperature Measurement Characteristic (0x2A1C)
   DISCONNECTED  // Receiving temperature values from the server
} discovery_state_t;

/**
 * @brief     Sets the event for LETIMER0 Underflow.
 *
 * This function signals the BLE stack when a temperature measurement event occurs.
 *
 * @param     None
 * @return    None
 */
void schedulerSetEventUF(void);

/**
 * @brief     Sets the event for LETIMER0 COMP1 (used for timer delays).
 *
 * This function signals when a timer delay has expired.
 *
 * @param     None
 * @return    None
 */
void schedulerSetEventCOMP1(void);

/**
 * @brief     Sets the event when an I2C transaction is complete.
 *
 * This function is called after an I2C read operation completes, signaling
 * that the temperature data is available.
 *
 * @param     None
 * @return    None
 */
void schedulerSetEventI2CComplete(void);
/**
 * @brief Schedules an event when PB0 is pressed.
 *
 * This function is called when the PB0 button is detected as pressed. It signals
 * the BLE stack by sending an external event (`PB0_EVENT`), which can be handled
 * in the BLE event loop.
 *
 * @param None
 * @return None
 */
void schedulerSetEventPB0Pressed(void);
/**
 * @brief Schedules an event when PB0 is released.
 *
 * This function is called when the PB0 button is detected as released. It signals
 * the BLE stack by sending an external event (`PB0_RELEASED`), which can be handled
 * in the BLE event loop.
 *
 * @param None
 * @return None
 */
void schedulerSetEventPB0Released(void);
/**
 * @brief     Implements the state machine for temperature measurement.
 *
 * This function processes events for reading sensor data and transmitting it over BLE.
 *
 * @param     evt  Pointer to the Bluetooth event structure (sl_bt_msg_t).
 * @return    None
 */
void state_machine(sl_bt_msg_t *evt);
/**
 * @brief Handles the BLE discovery state machine for service and characteristic discovery.
 *
 * This function transitions through various states to establish a connection, discover
 * the Health Thermometer Service (HTM), identify the temperature characteristic, enable
 * notifications, and handle disconnections.
 *
 *
 * @param evt Pointer to the Bluetooth event structure (`sl_bt_msg_t`).
 *
 * @return None (void). Updates the discovery state and configures BLE services.
 */
void discovery_state_machine(sl_bt_msg_t *evt);
#endif /* SCHEDULER_H_ */







