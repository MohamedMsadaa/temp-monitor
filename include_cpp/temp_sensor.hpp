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

#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

#include <cstdint>
#include <cstdbool>

namespace tempMonitor {

/**
 * @brief Represents a generic temperature sensor.
 */
class Sensor {
private:
    /* Constants / Default */
    static constexpr uint32_t CfgDefaultTempSamplingPeriod = static_cast<uint32_t>(100); // 100us

    /* members */
    bool m_is_temp_manager_init{false};
    uint32_t m_sampling_periode;

protected:
    bool read_raw_adc_value(uint16_t &raw_value);

public:
    Sensor() : m_sampling_periode(CfgDefaultTempSamplingPeriod){};
    Sensor(uint32_t sampling_period) : m_sampling_periode(sampling_period){};
    virtual ~Sensor() = default;

    bool init();
    bool is_new_data_available();
    uint32_t sampling_period();
    void deinit();

    virtual bool read_temperature(float &temp_value) = 0;
};

/**
 * @brief Represents a RevA temperature sensor.
 */
class SensorRevA : public Sensor {
private:
    static constexpr float CfgHwTempScale = static_cast<float>(1.0f);
public:
    SensorRevA(uint32_t sampling_period) : Sensor(sampling_period) {};
    bool read_temperature(float &temp_value) override ;
};

/**
 * @brief Represents a RevB temperature sensor.
 */
class SensorRevB : public Sensor {
private:
    static constexpr float CfgHwTempScale = static_cast<float>(0.1f);
public:
    SensorRevB(uint32_t sampling_period) : Sensor(sampling_period) {};
    bool read_temperature(float &temp_value) override ;
};

}
#endif /* TEMP_SENSOR_H */