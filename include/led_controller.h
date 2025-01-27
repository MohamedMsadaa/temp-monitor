/******************************************************************************
 * File Name:   led_controller.h
 * Description: This file contains the implementation of led controller using 
 *              GPIO Driver.
 * 
 * 
 * Author:      Mohamed Msadaa
 * Date:        January 26, 2025
 * Version:     1.0.0
 * License:     MIT License
 *
 * Dependencies: Hardware
 *              Doxygen for documentation generation
 *
 *****************************************************************************/

#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <stdint.h>
#include <stdbool.h>

/******************************************************************************
 *                  STRUCTURE / ENUM DEFINITIONS SECTION
 *****************************************************************************/
/**
 * @brief Enum representing the led id
 *        assuming it is one to one 
 *        with gpio pins as well.
 *
 */
typedef enum {
    LED_INVALID_ID = 0,
    LED_GREEN_ID = 1,
    LED_YELLOW_ID = 2,
    LED_RED_ID = 3
} led_id_t;

/**
 * @brief Enum representing the led id.
 *
 */
typedef enum {
    LED_STATE_INVALID = 0,
    LED_STATE_ON = 1,
    LED_STATE_OFF = 2
} led_state_t;


/******************************************************************************
 *                    PUBLIC FUNCTIONS DEFINITIONS SECTION
 *****************************************************************************/
/**
 * @brief Led controller intialization
 * 
 * This function will initialize GPIO of leds.
 * 
 * @param none
 * @return bool true if successful
 */
bool led_controller_init(void) ;

/**
 * @brief led controller set led
 * 
 * This function will turn off on leds.
 * 
 * @param id led_id_t the id of led
 * @param state led_state_t the state of led on or off.
 * @return true if successful
 */
bool led_controller_set_state(led_id_t id, led_state_t state) ;

/**
 * @brief set gyr led state
 * .
 * 
 * @param green led_state_t state of green led
 * @param yellow led_state_t state of yellow led
 * @param red led_state_t state of red led
 * @return bool true if successful
 */
bool led_controller_set_leds_state(led_state_t green_state, led_state_t yellow_state, led_state_t red_state);

/**
 * @brief led get state
 * 
 * This function will read the led state.
 * 
 * @param id led_id_t the id of led
 * @param state led_state_t pointer to the state of led on or off.
 * @return true if successful
 */
bool led_controller_get_state(led_id_t id, led_state_t *state) ;

/**
 * @brief led controller shutdown
 * 
 * This function will turn off all leds.
 * 
 * @param none
 * @return void
 */
void led_controller_shutdown() ;

#endif /* LED_CONTROLLER_H */