/******************************************************************************
 * File Name:   temp_manager.h
 * Description: This file contains the implementation of temperator sensor 
 *              using ADC conversion.
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

#include <stdint.h>
#include <stdbool.h>

/******************************************************************************
 *                  MACROS / TYPES DEFINITIONS SECTION
 *****************************************************************************/
/**
 * @brief Enum representing teperature status.
 *
 */
typedef enum {
    TEMP_STATUS_INVALID = 0,
    TEMP_STATUS_NORMAL = 1,
    TEMP_STATUS_WARNING = 2,
    TEMP_STATUS_CRITICAL = 3
} temp_status_t;

#define CFG_TEMP_SAMPLING_PERIOD_US          100 // in us

/******************************************************************************
 *                 PUBLIC FUNCTIONS DEFINITIONS SECTION
 *****************************************************************************/

/**
 * @brief Temp sensor initialization
 * 
 * This function will will initialize temperator sensor.
 * 
 * @param none
 * @return bool true if successful
 */
bool temp_manager_init(void) ;

/**
 * @brief read temperature status
 * 
 * This function will read temperature status
 * 
 * @param none
 * @return temp_status_t status of temp critical / ...
 */
temp_status_t temp_manager_read_status() ;

/**
 * @brief check if new value is available
 * 
 * This function will return true once if new value available.
 * 
 * @param none
 * @return bool true if new data available
 */
bool temp_manager_is_new_data_available() ;

/**
 * @brief stop temperature sensor reading
 * 
 * This function will stop temperatur reading.
 * 
 * @param none
 * @return void
 */
void temp_manager_shutdown() ;

#endif /* TEMP_MANAGER_H */