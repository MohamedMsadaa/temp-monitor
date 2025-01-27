/**
 * @file main.cpp
 * @brief Temperature Monitoring and Visualization System
 *
 * This file contains the main entry point as bare metal OS for the temperature monitoring system.
 * The system reads temperature values from an ADC, processes them, and controls
 * LED indicators based on predefined temperature thresholds.
 *
 * @author Mohamed Msadaa
 * @date 26.01.2025
 * @version 1.0
 *
 * @note This project is designed for demo purposes with mocked hardware.
 */

extern "C" {
    #include "eeprom_driver.h"
}

#include "led_controller.hpp"
#include "sensor_factory.hpp"
#include "temp_sensor.hpp"
#include "temp_manager.hpp"

namespace tmon = tempMonitor;

static constexpr uint32_t CfgSamplingPeriod = 100;

int main() {
    /* Init EEPROM */
    HAL_eeprom_init();

    /* Create instance sensor and LED controller */
    auto sensor = tmon::SensorFactory::create_sensor(CfgSamplingPeriod);
    auto led_controller = std::make_unique<tmon::LedController>();

    tmon::Manager *temp_manager = tmon::Manager::get_instance(std::move(sensor), std::move(led_controller));
    
    temp_manager->init();

    /* infinite loop */
    while (true) {
        temp_manager->monitor_temperature();

        /* Other functionality */
    }

    temp_manager->shutdown(); 

    return 0;
}