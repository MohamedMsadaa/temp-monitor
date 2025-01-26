/******************************************************************************
 * File Name:   timer_driver.h
 * Description: This file contains the hardware abstraction layer of Timer.
 * 
 * Author:      Mohamed Msadaa
 * Date:        January 25, 2025
 * Version:     1.0.0
 * License:     MIT License
 *
 * Dependencies: Hardware??
 *              Doxygen for documentation generation
 *****************************************************************************/

#ifndef TIMER_DRIVER_H
#define TIMER_DRIVER_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef void (*callback_t)(void);

/**
 * @brief hardware timer interruption handler
 * 
 * This interruption handle elapsed timer event and will trigger callback 
 * if it is configured at a the configured interval. It also automatically 
 * restart the timer if feature is activated.
 * 
 * @param none
 * @return void
 */
void HAL_timer_irq_handler(void);

/**
 * @brief hardware timer initialization
 * 
 * This function initialize hardware timer and configure it.
 * 
 * @param period uint16_t timer period
 * @param callback callback_t to be called when timer elapsed
 * @param auto_start bool is timer auto start feature active
 * @return bool true if init successful
 */
bool HAL_timer_init(uint16_t period, callback_t callback, bool auto_start);

/**
 * @brief hardware timer start
 * 
 * This function starts hardware timer.
 * 
 * @param none
 * @return bool true if successful
 */
bool HAL_timer_start();

/**
 * @brief hardware timer stop
 * 
 * This function stops hardware timer.
 * 
 * @param none
 * @return bool true if successful
 */
bool HAL_timer_stop();

#endif /* TIMER_DRIVER_H */