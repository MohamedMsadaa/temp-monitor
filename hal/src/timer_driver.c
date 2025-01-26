#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "timer_driver.h"

/******************************************************************************
 *                          MACRO DEFINITIONS SECTION
 *****************************************************************************/
#define TIMER_INIT()     (printf("Mock: Init TIMER\n"))   // Init TIMER
#define TIMER_START()    (printf("Mock: Start TIMER\n"))   // Start TIMER
#define TIMER_STOP()     (printf("Mock: Stop TIMER \n"))   // Stop TIMER 
#define TIMER_RESTART()  (printf("Mock: Restart TIMER \n"))   // Restart TIMER 

/******************************************************************************
 *                    GLOBAL VARIABLES DEFINITIONS SECTION
 *****************************************************************************/
volatile callback_t g_callback = NULL;
volatile bool g_auto_start = false;
static bool g_is_timer_init = false;
static bool g_is_timer_started = false;

/******************************************************************************
 *                    PUBLIC FUNCTIONS DEFINITIONS SECTION
 *****************************************************************************/

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
void HAL_timer_irq_handler(void) {
    if (g_callback) {
        /* trigger callback function */
        g_callback();
    }
    
    if (g_auto_start) { 
        TIMER_RESTART();
    }
}

/**
 * @brief hardware timer initialization
 * 
 * This function initialize hardware timer and configure it.
 * 
 * @param period uint16_t timer period
 * @param callback callback_t to be called when timer elapsed
 * @param auto_start bool is timer auto start feature active
 * @return void
 */
bool HAL_timer_init(uint16_t period, callback_t callback, bool auto_start) {
    /* TODO Configure HW Timer interruption */
    TIMER_INIT();

    /* configure timer period */
    g_callback = callback;
    g_auto_start = auto_start;
    g_is_timer_init = true;

    return true; /* for mock it will always be true */
}

/**
 * @brief hardware timer start
 * 
 * This function starts hardware timer.
 * 
 * @param none
 * @return bool true if successful
 */
bool HAL_timer_start() {
    if (!g_is_timer_init) {
        return false;
    }

    /* Make sure timer is stopped */
    if (!g_is_timer_started) {
        /* code */
        TIMER_START();
        g_is_timer_started = true;
    }
    
    return true;
}

/**
 * @brief hardware timer stop
 * 
 * This function stops hardware timer.
 * 
 * @param none
 * @return bool true if successful
 */
bool HAL_timer_stop() {
    if (g_is_timer_started) {
        /* code */
        TIMER_STOP();
        g_is_timer_started = false;
    }
    
    return true;
}