#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "eeprom_driver.h"

/******************************************************************************
 *                  MOCK HARDWARE REGISTER DEFINITIONS SECTION
 *****************************************************************************/


/******************************************************************************
 *                    GLOBAL VARIABLES DEFINITIONS SECTION
 *****************************************************************************/


/******************************************************************************
 *                    PUBLIC FUNCTIONS DEFINITIONS SECTION
 *****************************************************************************/

/**
 * @brief EEPROM init function
 * 
 * This function will init EEPROM.
 * 
 * @param none might require paraneters
 * @return bool true if successful
 */
bool HAL_eeprom_init() {
    /* Init EEPROM */
    return true;
}

/**
 * @brief EEPROM read function
 * 
 * This function will read value from EEPROM.
 * 
 * @param address uint32_t address of eeprom to read from
 * @param address uint32_t * pointer of value
 * @return bool true if successful
 */
bool HAL_eeprom_read(uint32_t address, uint32_t *value) {
    /* Read EEPROM from address */
    if (!value) {
        return false;
    }
    
    *value = *value;
    return true;
}

/**
 * @brief EEPROM read function
 * 
 * This function will read value in string form from EEPROM.
 * 
 * @param address uint32_t address of eeprom to read from
 * @param address char * pointer of char array
 * @return bool true if successful
 */
bool HAL_eeprom_read_string(uint32_t address, char *value, uint32_t size) {
    /* Read EEPROM from address */
    if (!value) {
        return false;
    }
    if (size == 0) {
        return false;
    }
    
    *value = *value;
    return true;
}
