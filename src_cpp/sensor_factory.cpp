
extern "C" {
    #include "eeprom_driver.h"
    #include "eeprom_config.h"
}

#include "temp_sensor.hpp"
#include "sensor_factory.hpp"

namespace tmon = tempMonitor;

/******************************************************************************
 *                    SENSOR FACTORY FUNCTIONS DEFINITIONS SECTION
 *****************************************************************************/

/**
 * @brief init sensor
 * 
 * This function will initialize sensor using adc.
 * 
 * @param none 
 * @return bool true if successful
 */
std::unique_ptr<tmon::Sensor> tmon::SensorFactory::create_sensor(uint32_t sampling_periode) {
    uint32_t value ;
    if (HAL_eeprom_read(EEPROM_HW_REV_ADDR, &value)) {
        auto hw_rev = static_cast<Hardware>(value);
        if (hw_rev == Hardware::RevB) {
            return std::make_unique<tempMonitor::SensorRevB>(sampling_periode);
        } else {
            return std::make_unique<tempMonitor::SensorRevA>(sampling_periode);
        }
    }
    /* Default is RevA */
    return std::make_unique<tempMonitor::SensorRevA>(sampling_periode);
}