#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "eeprom_config.h"
#include "eeprom_driver.h"
#include "adc_driver.h"
#include "temp_manager.h"

/******************************************************************************
 *                  MACROS / TYPES DEFINITIONS SECTION
 *****************************************************************************/
/**
 * @brief Enum representing hardware revision.
 *
 */
typedef enum {
    HW_REV_A = 0,
    HW_REV_B = 1
} hw_rev_t;

#define CFG_MAX_NORMAL_OPERATION_TEMP        85.0f
#define CFG_CRITICAL_UPPER_THRESHOLD_TEMP    105.0f
#define CFG_CRITICAL_LOWER_THRESHOLD_TEMP    5.0f

#define CFG_HW_REVA_TEMP_SCALE               1.0f // 1 unit correspond to 1 degree celcius
#define CFG_HW_REVB_TEMP_SCALE               0.1f // 1 unit correspond to 0.1 degree celcius

/******************************************************************************
 *                    GLOBAL VARIABLES DEFINITIONS SECTION
 *****************************************************************************/

static hw_rev_t g_hw_rev = HW_REV_A;  // default is revision A
static bool g_is_temp_manager_init = false;

/******************************************************************************
 *                    PRIVATE FUNCTIONS DEFINITIONS SECTION
 *****************************************************************************/
/**
 * @brief read temperatur value
 * 
 * This function will read temperature.
 * 
 * @param float temp sclaed temp based on revision in degree celcuis
 * @return bool true if successful
 */
static bool temp_manager_read(float * temp) {
    if (!g_is_temp_manager_init) {
        return false;
    }
    
    uint16_t adc_value = HAL_ADC_read();
    if(g_hw_rev == HW_REV_B) {
        *temp = (float)adc_value * CFG_HW_REVA_TEMP_SCALE;
    } else {
        *temp = (float)adc_value * CFG_HW_REVB_TEMP_SCALE;
    }
    return true;
}

/******************************************************************************
 *                    PUBLIC FUNCTIONS DEFINITIONS SECTION
 *****************************************************************************/

/**
 * @brief Temp sensor initialization
 * 
 * This function will will initialize temperator sensor.
 * 
 * @param none
 * @return bool true if successful
 */
bool temp_manager_init(void) {
    bool result = true;

    result &= HAL_eeprom_init();
    /* Read EEPROM hw rev and stored in RAM for fast access */
    result &= HAL_eeprom_read(EEPROM_HW_REV_ADDR, &g_hw_rev);

    /* Init ADC */
    result &= HAL_ADC_init(CFG_TEMP_SAMPLING_PERIOD_US);

    if(result) {
        g_is_temp_manager_init = true;
    }

    return result;
}

/**
 * @brief temperature status
 * 
 * This function will evaluate temperature status
 * 
 * @param none
 * @return temp_status_t status of temp critical / ...
 */
temp_status_t temp_manager_evaluate_status() {
    float temp_value = 0.0f;
    temp_status_t status = TEMP_STATUS_INVALID;

    if (temp_manager_read(&temp_value)) {
        if (temp_value < CFG_CRITICAL_LOWER_THRESHOLD_TEMP || temp_value >= CFG_CRITICAL_UPPER_THRESHOLD_TEMP) {
            status = TEMP_STATUS_CRITICAL;
        } 
        else if (temp_value >= CFG_MAX_NORMAL_OPERATION_TEMP) {
            status = TEMP_STATUS_WARNING;
        } 
        else {
            status = TEMP_STATUS_NORMAL;
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
bool temp_manager_is_new_data_available() {
    return HAL_ADC_is_new_data_available();
}

/**
 * @brief stop temperature sensor reading
 * 
 * This function will stop temperatur reading.
 * 
 * @param none
 * @return void
 */
void temp_manager_shutdown() {
    g_is_temp_manager_init = false;
    HAL_ADC_shutdown();
}