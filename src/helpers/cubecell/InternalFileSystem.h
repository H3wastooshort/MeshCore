#pragma once

#include <Arduino.h>
#include "Adafruit_LittleFS.h"
#define EEPROM_PAGES 3
#define EEPROM_PAGESIZE CY_FLASH_SIZEOF_ROW
#define EEPROM_SIZE (EEPROM_PAGESIZE * EEPROM_PAGES)
#define EEPROM_RWSIZE 8
#define EEPROM_BASE CY_SFLASH_USERBASE

 class InternalFileSystem : public Adafruit_LittleFS
 {
   public:
     InternalFileSystem(void);
 
     // overwrite to also perform low level format (sector erase of whole flash region)
     bool begin(void);
 };
 
 extern InternalFileSystem InternalFS;
 