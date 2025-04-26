/***************************************************************************//**
 * @file
 * @brief Application interface provided to main().
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 *
 * Editor: Feb 26, 2022, Dave Sluiter
 * Change: Added comment about use of .h files.
 *
 *
 *
 * Student edit: Add your name and email address here:
 * @student    Awesome Student, Awesome.Student@Colorado.edu
 *
 *
 ******************************************************************************/

// Students: Remember, a header file (a .h file) defines an interface
//           for functions defined within an implementation file (a .c file).
//           The .h file defines what a caller (a user) of a .c file requires.
//           At a minimum, the .h file should define the publicly callable
//           functions, i.e. define the function prototypes. #define and type
//           definitions can be added if the caller requires theses.

#ifndef APP_H
#define APP_H
#include <stdint.h>
//defining the macro for the lowest energy modes
//So for EM0/EM1/EM2/EM3 modes the numeric values are as  0/1/2/3

//#define LOWEST_ENERGY_MODE (0)
//#define LOWEST_ENERGY_MODE (1)
#define LOWEST_ENERGY_MODE (2)
//#define LOWEST_ENERGY_MODE   (3)


typedef enum {
    STATE_IDLE,
    STATE_POWER_ON_SENSOR,
    STATE_I2C_WRITE_COMPLETE,
    STATE_WAIT_FOR_MEASUREMENT,
    STATE_READ_TEMPERATURE,

} state_t;
/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
/**
 * @brief  Initializes the application.
 *
 * This function initializes essential system components such as
 * GPIO, oscillators, timers, and I2C communication. It also configures
 * power management requirements based on the lowest selected energy mode.
 *
 * @param  None
 * @return None
 */
void app_init(void);

/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
/**
 * @brief Processes scheduled events.
 *
 * This function fetches the next scheduled event from the event queue and
 * passes it to the state machine for further processing.
 *
 * @param None
 * @return None
 */
void app_process_action(void);
/**
 * @brief Handles the state transitions based on events.
 *
 * This function manages the state transitions of the system based on
 * the received event. It implements a finite state machine to process
 * sensor readings, manage power states, and control I2C transactions.
 *
 * @param currentState Pointer to the current state of the system.
 * @param The event that triggers state transitions.
 * @return None
 */
void handle_state_machine(state_t *currentState, uint32_t evt);

#endif // APP_H
