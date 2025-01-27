/******************************************************************************
 * File Name:   temp_sensor.hpp
 * Description: This file contains the implementation of temperature sensor 
 *              using ADC HAL.
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

#ifndef TEMP_MANAGER_H
#define TEMP_MANAGER_H

#include <iostream>
#include <cstdint>
#include <cstdbool>
#include <memory>

#include "temp_sensor.hpp"
#include "led_controller.hpp"

namespace tempMonitor {

/******************************************************************************
 *                  MACROS / TYPES DEFINITIONS SECTION
 *****************************************************************************/
/**
 * @brief Enum representing temperature status.
 *
 */
enum class TempStatus{
    Invalid = 0,
    Normal = 1,
    Warning = 2,
    Critical = 3
};

class Manager {
private:
    /* Constants */
    static constexpr float CfgMaxNormalOperationTemp = 85.0f; // in degree celcuis
    static constexpr float CfgCriticalUpperThresholdTemp = 105.0f; // in degree celcuis
    static constexpr float CfgCriticalLowerThresholdTemp = 5.0f; // in degree celcuis

    static std::unique_ptr<Manager> m_instance;
    std::unique_ptr<Sensor> m_sensor;
    std::unique_ptr<LedController> m_led_controller;
    bool m_is_init {false};

    /* Private constructor to enforce singleton pattern */
    Manager(std::unique_ptr<Sensor> sensor, std::unique_ptr<LedController> led_controller)
        : m_sensor(std::move(sensor)), m_led_controller(std::move(led_controller)) {}

    /**
     * @brief evaluate temperature status
     * 
     * This function will read temperature status
     * 
     * @param none
     * @return TempStatus status of temp critical / ...
     */
    TempStatus evaluate_status() ;

    /**
     * @brief check if new value is available
     * 
     * This function will return true once if new value available.
     * 
     * @param none
     * @return bool true if new data available
     */
    bool is_new_data_available() ;

public:
    virtual ~Manager() = default;

    /* Static function to create instance */
    static Manager* get_instance(std::unique_ptr<Sensor> sensor, std::unique_ptr<LedController> led_controller);

    /* Delete operators to avoid singleton to be copied */
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;

    /**
     * @brief manager initialization
     * 
     * This function will will initialize temperator manager.
     * 
     * @param none
     * @return bool true if successful
     */
    bool init(void) ;    
    
    /**
     * @brief monitor temperature
     * 
     * This function will monitor temperature.
     * 
     * @param none
     * @return void
     */
    void monitor_temperature(void) ;

    /**
     * @brief stop temperature manager
     * 
     * This function will stop temperature reading.
     * 
     * @param none
     * @return void
     */
    void shutdown() ;
};

}// namespace tempMonitor

#endif /* TEMP_MANAGER_H */