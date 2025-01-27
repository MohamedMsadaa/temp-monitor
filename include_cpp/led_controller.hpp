/******************************************************************************
 * File Name:   led_controller.hpp
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

#include <cstdint>
#include <cstdbool>

namespace tempMonitor {

/******************************************************************************
 *                  CLASS / ENUM DEFINITIONS SECTION
 *****************************************************************************/
/**
 * @brief Enum representing the led id
 *        assuming it is one to one 
 *        with gpio pins as well.
 *
 */
enum class Led : uint8_t {
    Invalid = 0,
    Green = 1,
    Yellow = 2,
    Red = 3
};

/**
 * @brief Enum representing the led state.
 *
 */
enum class LedState : uint8_t {
    Invalid = 0,
    On = 1,
    Off = 2
};

/**
 * @brief class to control leds.
 *
 */
class LedController {
private:
    bool m_is_init {false};
public:
    LedController() = default; 
    virtual ~LedController() = default;

    /**
     * @brief Led controller intialization
     * 
     * This function will initialize GPIO of leds.
     * 
     * @param none
     * @return bool true if successful
     */
    bool init(void) ;

    /**
     * @brief led controller set led
     * 
     * This function will turn off on leds.
     * 
     * @param id Led the id of led
     * @param state LedState the state of led on or off.
     * @return true if successful
     */
    bool set_state(Led id, LedState state) ;

    /**
     * @brief led get state
     * 
     * This function will read the led state.
     * 
     * @param id led_id_t the id of led
     * @param state led_state_t pointer to the state of led on or off.
     * @return bool true if successful
     */
    bool get_state(Led id, LedState &state) ;

    /**
     * @brief set rgb led state
     * .
     * 
     * @param green_state LedState state of green led
     * @param yellow_state LedState state of yellow led
     * @param red_state LedState state of red led
     * @return bool true if successful
     */
    bool set_leds_state(LedState green_state, LedState yellow_state, LedState red_state);

    /**
     * @brief led controller shutdown
     * 
     * This function will turn off all leds.
     * 
     * @param none
     * @return void
     */
    void shutdown() ;
};

}

#endif /* LED_CONTROLLER_H */