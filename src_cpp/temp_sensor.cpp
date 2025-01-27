
extern "C" {
    #include "adc_driver.h"
}
#include "temp_sensor.hpp"

namespace tmon = tempMonitor;

/******************************************************************************
 *                    SENSOR FUNCTIONS DEFINITIONS SECTION
 *****************************************************************************/

/**
 * @brief init sensor
 * 
 * This function will initialize sensor using adc.
 * 
 * @param none 
 * @return bool true if successful
 */
bool tmon::Sensor::init() {
    auto result = true;
    
    /* Init ADC */
    result &= HAL_ADC_init(m_sampling_periode);

    if(result) {
        m_is_temp_manager_init = true;
    }

    return result;
}

/**
 * @brief read raw value
 * 
 * This function will read raw adc value.
 * 
 * @param uint16 raw_value
 * @return bool true if successful
 */
bool tmon::Sensor::read_raw_adc_value(uint16_t &raw_value) {
    if (!m_is_temp_manager_init) {
        return false;
    }
    
    raw_value = HAL_ADC_read();
    return true;
}

/**
 * @brief check if new value is available
 * 
 * This function will return true once if new value available.
 * 
 * @param none
 * @return bool true if new data available
 */
bool tmon::Sensor::is_new_data_available() {
    return HAL_ADC_is_new_data_available();
}

/**
 * @brief return configured sampling period
 * 
 * 
 * @param none
 * @return uint32_t sampling period in us
 */
uint32_t tempMonitor::Sensor::sampling_period() {
    return m_sampling_periode;
}

/**
 * @brief stop temperature sensor reading
 * 
 * This function will stop temperatur reading.
 * 
 * @param none
 * @return void
 */
void tmon::Sensor::deinit() {
    m_is_temp_manager_init = false;
    HAL_ADC_shutdown();
}

/******************************************************************************
 *                    SENSOR RevA FUNCTIONS DEFINITIONS SECTION
 *****************************************************************************/

/**
 * @brief read temprature RevA
 * 
 * This function will read temperature based on hardware scaling.
 * 
 * @param float temp_value
 * @return bool true if successful
 */
bool tmon::SensorRevA::read_temperature(float &temp_value) {
    uint16_t raw_value = 0;

    if (!read_raw_adc_value(raw_value)) {
        return false;
    }
    
    temp_value = static_cast<float>(raw_value) * CfgHwTempScale;
    return true;
}

/******************************************************************************
 *                    SENSOR RevB FUNCTIONS DEFINITIONS SECTION
 *****************************************************************************/

/**
 * @brief read temprature RevB
 * 
 * This function will read temperature based on hardware scaling.
 * 
 * @param float temp_value
 * @return bool true if successful
 */
bool tmon::SensorRevB::read_temperature(float &temp_value) {
    uint16_t raw_value = 0;

    if (!read_raw_adc_value(raw_value)) {
        return false;
    }
    
    temp_value = static_cast<float>(raw_value) * CfgHwTempScale;
    return true;
}