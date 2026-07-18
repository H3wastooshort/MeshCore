#pragma once

#include <Arduino.h>
#include "Adafruit_LittleFS.h"

#ifdef __asr650x__
  #define EEPROM_BASE CY_SFLASH_USERBASE
  #define EEPROM_PAGES 3
  #define EEPROM_PAGESIZE CY_FLASH_SIZEOF_ROW
  #define EEPROM_SIZE (EEPROM_PAGESIZE * EEPROM_PAGES)
#else
  #define EEPROM_BASE FLASH_BASE+0x7400
  #define EEPROM_SIZE 0xC00
  #define EEPROM_PAGESIZE 256
#endif

#define EEPROM_RWSIZE 8

class InternalFileSystem : public Adafruit_LittleFS
{
  public:
    InternalFileSystem(void);

    // overwrite to also perform low level format (sector erase of whole flash region)
    bool begin(void);
};

extern InternalFileSystem InternalFS;
 