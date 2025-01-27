
extern "C" {
    #include "gpio_driver.h"
    #include "interruption.h"
}

#include "led_controller.hpp"

namespace tmon = tempMonitor;

/******************************************************************************
 *                    PRIVATE FUNCTIONS DEFINITIONS SECTION
 *****************************************************************************/

/**
 * @brief gpio state conversion
 * 
 * This function will convert gpio state to led state.
 * 
 * @param gpio_state_t state
 * @return LedState 
 */
static tmon::LedState convert_gpio_2_led_state(gpio_state_t state) {
    switch (state)
    {
    case GPIO_STATE_HIGH: return tmon::LedState::On;
    case GPIO_STATE_LOW: return tmon::LedState::Off;
    
    default:return tmon::LedState::Invalid;
    }
}

/**
 * @brief Led state conversion
 * 
 * This function will convert led state to gpio state.
 * 
 * @param LedState state
 * @return gpio_state_t 
 */
static gpio_state_t convert_led_2_gpio_state(tmon::LedState state) {
    switch (state)
    {
    case tmon::LedState::On: return GPIO_STATE_HIGH;
    case tmon::LedState::Off: return GPIO_STATE_LOW;
    
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
bool tmon::LedController::init(void) {
    bool result = true;

    result &= HAL_gpio_init(static_cast<uint8_t>(tmon::Led::Green), GPIO_MODE_OUTPUT);
    result &= HAL_gpio_init(static_cast<uint8_t>(tmon::Led::Yellow), GPIO_MODE_OUTPUT);
    result &= HAL_gpio_init(static_cast<uint8_t>(tmon::Led::Red), GPIO_MODE_OUTPUT);

    if (result) {
        m_is_init = true;
    }

    /* Reset led state */
    result &= HAL_gpio_set(static_cast<uint8_t>(tmon::Led::Green), GPIO_STATE_LOW);
    result &= HAL_gpio_set(static_cast<uint8_t>(tmon::Led::Yellow), GPIO_STATE_LOW);
    result &= HAL_gpio_set(static_cast<uint8_t>(tmon::Led::Red), GPIO_STATE_LOW);
    
    return result;
}

/**
 * @brief led controller set led
 * 
 * This function will turn off on leds.
 * 
 * @param id led the id of led
 * @param state LedState the state of led on or off.
 * @return true if successful
 */
bool tmon::LedController::set_state(tmon::Led id, tmon::LedState state) {
    if ((id < tmon::Led::Green) & (id > tmon::Led::Red)) {
        return false;
    }

    if (!m_is_init) {
        return false;
    }
    
    return HAL_gpio_set(static_cast<uint8_t>(id), convert_led_2_gpio_state(state));
}

/**
 * @brief led get state
 * 
 * This function will read the led state.
 * 
 * @param id Led the id of led
 * @param state LedState pointer to the state of led on or off.
 * @return true if successful
 */
bool tmon::LedController::get_state(tmon::Led id, tmon::LedState &state) {
    if ((id < tmon::Led::Green) & (id > tmon::Led::Red)) {
        return false;
    }

    if (!m_is_init) {
        return false;
    }

    gpio_state_t gpio_state = GPIO_STATE_LOW;
    bool result = HAL_gpio_get(static_cast<uint8_t>(id), &gpio_state);

    state = convert_gpio_2_led_state(gpio_state);

    return result;
}

/**
 * @brief set gyr led state
 * .
 * 
 * @param green LedState state of green led
 * @param yellow LedState state of yellow led
 * @param red LedState state of red led
 * @return bool true if successful
 */
bool tmon::LedController::set_leds_state(tmon::LedState green_state, tmon::LedState yellow_state, tmon::LedState red_state) {
    bool result = true;
    result &= set_state(tmon::Led::Green, green_state);
    result &= set_state(tmon::Led::Yellow, yellow_state);
    result &= set_state(tmon::Led::Red, red_state);
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
void tmon::LedController::shutdown() {
    if (!m_is_init) {
        return;
    }

    m_is_init = false;
    
    /* Reset led state */
    (void)HAL_gpio_set(static_cast<uint8_t>(tmon::Led::Green), GPIO_STATE_LOW);
    (void)HAL_gpio_set(static_cast<uint8_t>(tmon::Led::Yellow), GPIO_STATE_LOW);
    (void)HAL_gpio_set(static_cast<uint8_t>(tmon::Led::Red), GPIO_STATE_LOW);
}
