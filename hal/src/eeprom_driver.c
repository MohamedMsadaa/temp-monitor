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
