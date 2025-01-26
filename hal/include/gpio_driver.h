/******************************************************************************
 * File Name:   gpio_driver.h
 * Description: This file contains the implementation of gpio hardware abstraction 
 *              layer to configure / read nad write to gpios.
 * 
 * 
 * Author:      Mohamed Msadaa
 * Date:        January 25, 2025
 * Version:     1.0.0
 * License:     MIT License
 *
 * Dependencies: Hardware
 *              Doxygen for documentation generation
 *
 *****************************************************************************/

#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include <stdint.h>
#include <stdbool.h>


/**
 * @brief Enum representing a GPIO mode.
 *
 */
typedef enum {
    GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT
} gpio_mode_t;

/**
 * @brief Enum representing a GPIO states.
 *
 */
typedef enum {
    GPIO_STATE_LOW = 0,
    GPIO_STATE_HIGH = 1
} gpio_state_t;

/**
 * @brief Structure representing a GPIO pin.
 *
 * This structure is used to define and configure a GPIO pin on the system. It contains
 * the pin number, the mode (input or output), and the current state (high or low)..
 */
typedef struct {
    uint8_t pin_number;   // Pin number 
    gpio_mode_t mode;     // Input/Output mode
    gpio_state_t state;   // Current state (LOW or HIGH)
} gpio_pin_t;

/**
 * @brief initialize GPIO
 * 
 * This function will initialize the adequate pin number mode.
 * 
 * @param pin uint8_t pin number
 * @param mode gpio_mode_t pin mode of operation
 * @return void
 */
void HAL_gpio_init(uint8_t pin, gpio_mode_t mode);

/**
 * @brief set GPIO status
 * 
 * This function will set pin state.
 * 
 * @param pin uint8_t pin number
 * @param state gpio_state_t pin state
 * @return void
 */
void HAL_gpio_set(uint8_t pin, gpio_state_t state);

/**
 * @brief read GPIO state
 * 
 * This function will read the pin state.
 * 
 * @param pin uint8_t pin number
 * @return gpio_state_t gpio state
 */
gpio_state_t HAL_gpio_read(uint8_t pin);

/**
 * @brief toggle GPIO state
 * 
 * This function will toggle pin state.
 * 
 * @param pin uint8_t pin number
 * @return void
 */
void HAL_gpio_toggle(uint8_t pin);

#endif /* GPIO_DRIVER_H */