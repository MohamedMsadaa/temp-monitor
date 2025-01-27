
extern "C" {
    #include "os.h"
    #include "interruption.h"
}

#include "eeprom_config.h"
#include "eeprom_driver.h"

#include "temp_manager.hpp"

namespace tmon = tempMonitor;

std::unique_ptr<tmon::Manager> tmon::Manager::m_instance = nullptr;

/******************************************************************************
 *                    PRIVATE FUNCTIONS DEFINITIONS SECTION
 *****************************************************************************/

/**
 * @brief temperature status
 * 
 * This function will evaluate temperature status
 * 
 * @param none
 * @return TempStatus status of temp critical / ...
 */
tmon::TempStatus tmon::Manager::evaluate_status() {
    float temp_value = 0.0f;
    TempStatus status = tmon::TempStatus::Invalid;

    if (m_sensor->read_temperature(temp_value)) {
        if (temp_value < CfgCriticalLowerThresholdTemp || temp_value >= CfgCriticalUpperThresholdTemp) {
            status = tmon::TempStatus::Critical;
        } 
        else if (temp_value >= CfgMaxNormalOperationTemp) {
            status = tmon::TempStatus::Warning;
        } 
        else {
            status = tmon::TempStatus::Normal;
        }
    }

    return status;
}

/**
 * @brief check if new value is available
 * 
 * This function will return true once if new value available.
 * 
 * @param none
 * @return bool true if new data available
 */
bool tmon::Manager::is_new_data_available() {
    if (!m_is_init) {
        return false;
    }
    
    return m_sensor->is_new_data_available();
}

/******************************************************************************
 *                    PUBLIC FUNCTIONS DEFINITIONS SECTION
 *****************************************************************************/

tmon::Manager* tmon::Manager::get_instance(std::unique_ptr<tmon::Sensor> sensor, std::unique_ptr<tmon::LedController> led_controller) {
    if (!m_instance) {
        /* As constractor is private make_unique cannot be used */
        m_instance = std::unique_ptr<Manager>(new Manager(std::move(sensor), std::move(led_controller)));
    }
    return m_instance.get();
}

/**
 * @brief Temp sensor initialization
 * 
 * This function will will initialize temperator sensor.
 * 
 * @param none
 * @return bool true if successful
 */
bool tmon::Manager::init(void) {
    /* Init sensor */
    if(!m_sensor->init()) {
        std::cerr << "[ERROR] Initializing temperature sensor!" << std::endl;
        return false;
    }

    /* Init controller */
    if(!m_sensor->init()) {
        std::cerr << "[ERROR] Initializing led controlle!" << std::endl;
        return false;
    }
    
    m_is_init = true;

    return true;
}

/**
 * @brief monitor temperature
 * 
 * This function will monitor temperature.
 * 
 * @param none
 * @return void
 */
void tmon::Manager::monitor_temperature(void) {
    /* Get current time in us */
    static uint32_t start_time = 0;
    uint32_t current_time = get_time_us();
    
    /* Check if it is not first run? */
    /* Sleep for remaining time for next sampling event */
    if (start_time != 0) {
        /* Compute execution time */
        uint32_t elapsed_time_us = current_time - start_time;
        if (elapsed_time_us < m_sensor->sampling_period()) {
            /* Sleep for the remaining time */
            sleep(m_sensor->sampling_period() - elapsed_time_us);
        }
    }

    /* Synchronize : Wait for temperature reading
        This will minimize jitter  */
    while (!is_new_data_available()) { 
        /* Sleep for one us to reduce CPU load */
        sleep(1); 
    };
    
    /* Evaluate temperature and control leds */
    static tmon::TempStatus previous_status = tmon::TempStatus::Invalid;
    auto status = evaluate_status();
    bool result = true;

   /* Update leds if temperature has changed or first time */
    if((previous_status != status)
        || (start_time == 0)) {
        switch (status) {
            case tmon::TempStatus::Critical:
                result &= m_led_controller->set_leds_state(tmon::LedState::Off, tmon::LedState::Off, tmon::LedState::On);
                break;

            case tmon::TempStatus::Warning:
                result &= m_led_controller->set_leds_state(tmon::LedState::Off, tmon::LedState::On, tmon::LedState::Off);
                break;

            case tmon::TempStatus::Normal:
                result &= m_led_controller->set_leds_state(tmon::LedState::On, tmon::LedState::Off, tmon::LedState::Off);
                break;
            
            default: /* Temperature reading failure set all LED ON */
                result &= m_led_controller->set_leds_state(tmon::LedState::On, tmon::LedState::On, tmon::LedState::On);
                std::cerr << "[ERROR] reading temp!" << std::endl;
                break;
        }
        if (!result) {
            std::cerr << "[ERROR] controlling LED!" << std::endl;
        }
    }

    start_time = current_time;
}

/**
 * @brief shutdown of sensor and controller
 * 
 * This function will stop temperature sensor reading and led controller.
 * 
 * @param none
 * @return void
 */
void tmon::Manager::shutdown() {
    if (!m_is_init) {
        return;
    }
    
    m_is_init = false;
    m_sensor->deinit();
    m_led_controller->shutdown();
}