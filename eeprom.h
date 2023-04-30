#include <stdbool.h>
#include <stdint.h>


void eeprom_set(uint32_t addr, uint8_t value);
uint8_t eeprom_get(uint32_t addr);
uint16_t eeprom_get_short(uint32_t addr);
uint32_t eeprom_get_long(uint32_t addr);
