#pragma once

#define RADIOLIB_STATIC_ONLY 1
#include <RadioLib.h>
#include <helpers/ArduinoHelpers.h>
#include <helpers/SensorManager.h>
#include <helpers/radiolib/CustomSX1262Wrapper.h>
#include <helpers/radiolib/RadioLibWrappers.h>
#include <helpers/cubecell/CubeCellBoard.h>

#define ADC_MULTIPLIER (5 * 1.73 * 1000)

class HTCCAB01Board : public CubeCellBoard
{
  public:
    void begin() override
    {
        CubeCellBoard::begin();
    }

    const char *getManufacturerName() const override { return "Tiny Relay"; }

    uint16_t getBattMilliVolts() override
    {
        uint32_t raw = 0;
        for (int i = 0; i < 8; i++) {
            raw += analogRead(PIN_VBAT_READ);
        }
        return ((double)raw) * ADC_MULTIPLIER / 8 / 4096;
    }

};

extern HTCCAB01Board board;
extern WRAPPER_CLASS radio_driver;
extern VolatileRTCClock rtc_clock;
extern SensorManager sensors;

bool radio_init();
mesh::LocalIdentity radio_new_identity();
