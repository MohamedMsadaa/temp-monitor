#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "gpio_driver.h"

/******************************************************************************
 *                  MOCK HARDWARE REGISTER DEFINITIONS SECTION
 *****************************************************************************/

/******************************************************************************
 *                    GLOBAL VARIABLES DEFINITIONS SECTION
 *****************************************************************************/


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
 * @return void
 */
void HAL_gpio_init(uint8_t pin, gpio_mode_t mode) {
    
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
void HAL_gpio_set(uint8_t pin, gpio_state_t state) {

}

/**
 * @brief read GPIO state
 * 
 * This function will read the pin state.
 * 
 * @param pin uint8_t pin number
 * @return gpio_state_t gpio state
 */
gpio_state_t HAL_gpio_read(uint8_t pin) {
    return GPIO_STATE_HIGH;
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

}
