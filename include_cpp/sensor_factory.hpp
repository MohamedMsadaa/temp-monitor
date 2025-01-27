/******************************************************************************
 * File Name:   sensor_factory.hpp
 * Description: This file contains the implementation of sensor factory.
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

#ifndef SENSOR_FACTORY_H
#define SENSOR_FACTORY_H

#include <cstdint>
#include <cstdbool>
#include <memory>

#include "temp_sensor.hpp"

namespace tempMonitor {

/**
 * @brief Represents a generic temperature sensor.
 */
class SensorFactory {
private:
    enum class Hardware {
        RevA = 0,
        RevB = 1,
    };
public:
    static std::unique_ptr<Sensor> create_sensor(uint32_t sampling_periode) ;
};

}
#endif /* SENSOR_FACTORY_H */