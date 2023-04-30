#include <string.h>

#include "eeprom.h"


static const uint8_t * nvm = (const uint8_t *)0x08007800;
static const size_t nvm_length = 0x800;

/* For the microcontroller STM32G030K6T6, the "6" in the eleventh position
 * indicates 32KiB of flash memory. This flash memory is at the range
 * 0x08000000 to 0x08007FFF (inclusive). This is organized into 16 pages (the
 * datasheet says 32 pages, but assumes a 64KiB device) of 2KiB each. There are
 * also "sub-pages" of flash, but they are not erasable individually. A 2KiB
 * page is the minimum erase size. Therefore, we use the flash range 0x08007800
 * to 0x08007FFF as the settings storage area. The range 0x08007000 to
 * 0x080077FF is reserved as an alternate, for a future design of a fully
 * journaled storage.
 */


void eeprom_set(uint32_t addr, uint8_t value)
{
}
uint8_t eeprom_get(uint32_t addr)
{
    return 0;
}
uint16_t eeprom_get_short(uint32_t addr)
{
    uint16_t lo = eeprom_get(addr);
    uint16_t hi = eeprom_get(addr + 1);
    return hi * 256 + lo;
}
uint32_t eeprom_get_long(uint32_t addr)
{
    uint32_t lo = eeprom_get_short(addr);
    uint32_t hi = eeprom_get_short(addr + 2);
    return hi * 65536 + lo;
}
