#pragma once

#define RADIOLIB_STATIC_ONLY 1
#include <RadioLib.h>
#include <helpers/ArduinoHelpers.h>
#include <helpers/SensorManager.h>
#include <helpers/radiolib/CustomSX1262Wrapper.h>
#include <helpers/radiolib/RadioLibWrappers.h>
#include <helpers/cubecell/CubeCellBoard.h>
#include <helpers/AutoDiscoverRTCClock.h>

//divider 10K to 1K => ratio 1/10
#define ADC_MULTIPLIER ((10*1)/1)
#define ADC_AVG_COUNT 8

class HTCCAB01Board : public CubeCellBoard
{
  public:
    void begin() override
    {
        CubeCellBoard::begin();
    }

    const char *getManufacturerName() const override { return "Heltec HTCC-AB01"; }

    uint16_t getBattMilliVolts() override
    {
        float raw = 0;
        for (int i = 0; i < ADC_AVG_COUNT; i++) {
            raw += analogReadmV(PIN_VBAT_READ);
        }
        return ((double)raw) * ADC_MULTIPLIER / ADC_AVG_COUNT;
    }

};

extern HTCCAB01Board board;
extern WRAPPER_CLASS radio_driver;
extern AutoDiscoverRTCClock rtc_clock;
extern SensorManager sensors;

bool radio_init();
mesh::LocalIdentity radio_new_identity();
