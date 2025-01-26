#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "gpio_driver.h"

/******************************************************************************
 *                  MOCK HARDWARE REGISTER DEFINITIONS SECTION
 *****************************************************************************/
#define  GPIO_PIN_COUNT  4

/******************************************************************************
 *                    GLOBAL VARIABLES DEFINITIONS SECTION
 *****************************************************************************/
static bool g_is_pin_init[GPIO_PIN_COUNT];

/******************************************************************************
 *                    PUBLIC FUNCTIONS DEFINITIONS SECTION
 *****************************************************************************/

/**
 * @brief initialize GPIO
 * 
 * This function will initialize the adequate pin number mode.
 * 
 * @param pin uint8_t pin number
 * @param mode gpio_mode_t pin mode of operation
 * @return true if successful
 */
bool HAL_gpio_init(uint8_t pin, gpio_mode_t mode) {
    if ((pin >= GPIO_PIN_COUNT)) {
        return false;
    }
    g_is_pin_init[pin] = true;
    /* init hardware */
    return true;
}

/**
 * @brief set GPIO status
 * 
 * This function will set pin state.
 * 
 * @param pin uint8_t pin number
 * @param state gpio_state_t pin state
 * @return void
 */
bool HAL_gpio_set(uint8_t pin, gpio_state_t state) {
    if ((pin >= GPIO_PIN_COUNT)) {
        return false;
    }

    if (!g_is_pin_init[pin]) {
        return false;
    }
    
    /* Set state */
    return true;
}

/**
 * @brief read GPIO state
 * 
 * This function will read the pin state.
 * 
 * @param pin uint8_t pin number
 * @param pin uint8_t pin number
 * @return gpio_state_t gpio state
 */
bool HAL_gpio_get(uint8_t pin, gpio_state_t *state) {
    if ((pin >= GPIO_PIN_COUNT)) {
        return false;
    }

    if (!g_is_pin_init[pin]) {
        return false;
    }

    if (!state) {
        return false;
    }
    
    /* Return state */
    *state = GPIO_STATE_HIGH;
    return true;
}

/**
 * @brief toggle GPIO state
 * 
 * This function will toggle pin state.
 * 
 * @param pin uint8_t pin number
 * @return void
 */
void HAL_gpio_toggle(uint8_t pin) {
    /* Unused */
}
