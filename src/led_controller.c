#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "interruption.h"
#include "gpio_driver.h"
#include "led_controller.h"

/******************************************************************************
 *                        MACRO DEFINITIONS SECTION
 *****************************************************************************/


/******************************************************************************
 *                    GLOBAL VARIABLES DEFINITIONS SECTION
 *****************************************************************************/

/******************************************************************************
 *                    PRIVATE FUNCTIONS DEFINITIONS SECTION
 *****************************************************************************/

/**
 * @brief gpio state conversion
 * 
 * This function will convert gpio state to led state.
 * 
 * @param gpio_state_t state
 * @return led_state_t 
 */
static led_state_t convert_gpio_2_led_state(gpio_state_t state) {
    switch (state)
    {
    case GPIO_STATE_HIGH: return LED_STATE_ON;
    case GPIO_STATE_LOW: return LED_STATE_OFF;
    
    default:return LED_STATE_OFF;
    }
}

/**
 * @brief Led state conversion
 * 
 * This function will convert led state to gpio state.
 * 
 * @param led_state_t state
 * @return gpio_state_t 
 */
static gpio_state_t convert_led_2_gpio_state(led_state_t state) {
    switch (state)
    {
    case LED_STATE_ON: return GPIO_STATE_HIGH;
    case LED_STATE_OFF: return GPIO_STATE_LOW;
    
    default:return GPIO_STATE_LOW;
    }
}

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
bool led_controller_init(void) {
    bool result = true;

    result &= HAL_gpio_init(LED_GREEN_ID, GPIO_MODE_OUTPUT);
    result &= HAL_gpio_init(LED_YELLOW_ID, GPIO_MODE_OUTPUT);
    result &= HAL_gpio_init(LED_RED_ID, GPIO_MODE_OUTPUT);

    /* Reset led state */
    result &= HAL_gpio_set(LED_GREEN_ID, GPIO_STATE_LOW);
    result &= HAL_gpio_set(LED_YELLOW_ID, GPIO_STATE_LOW);
    result &= HAL_gpio_set(LED_RED_ID, GPIO_STATE_LOW);
    
    return result;
}

/**
 * @brief led controller set led
 * 
 * This function will turn off on leds.
 * 
 * @param id led_id_t the id of led
 * @param state led_state_t the state of led on or off.
 * @return true if successful
 */
bool led_controller_set_state(led_id_t id, led_state_t state) {
    if ((id < LED_GREEN_ID) & (id > LED_RED_ID)) {
        return false;
    }
    return HAL_gpio_set(id, convert_led_2_gpio_state(state));
}

/**
 * @brief led get state
 * 
 * This function will read the led state.
 * 
 * @param id led_id_t the id of led
 * @param state led_state_t pointer to the state of led on or off.
 * @return true if successful
 */
bool led_controller_get_state(led_id_t id, led_state_t *state) {
    if ((id < LED_GREEN_ID) & (id > LED_RED_ID)) {
        return false;
    }
    gpio_state_t gpio_state = GPIO_STATE_LOW;
    bool result = HAL_gpio_get(id, &gpio_state);

    *state = convert_gpio_2_led_state(gpio_state);

    return result;
}

/**
 * @brief led controller shutdown
 * 
 * This function will turn off all leds.
 * 
 * @param none
 * @return void
 */
void led_controller_shutdown() {
    /* Reset led state */
    (void)HAL_gpio_set(LED_GREEN_ID, GPIO_STATE_LOW);
    (void)HAL_gpio_set(LED_YELLOW_ID, GPIO_STATE_LOW);
    (void)HAL_gpio_set(LED_RED_ID, GPIO_STATE_LOW);
}
