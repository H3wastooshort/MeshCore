#include "target.h"
#include <Arduino.h>
#include <helpers/ArduinoHelpers.h>

#if defined(P_LORA_SCLK)
  #define spi SPI
  RADIO_CLASS radio = new Module(P_LORA_NSS, P_LORA_DIO_1, P_LORA_RESET, P_LORA_BUSY, spi);
#else
  RADIO_CLASS radio = new Module(P_LORA_NSS, P_LORA_DIO_1, P_LORA_RESET, P_LORA_BUSY);
#endif


HTCCAB01Board board;

WRAPPER_CLASS radio_driver(radio, board);

VolatileRTCClock fallback_clock;
AutoDiscoverRTCClock rtc_clock(fallback_clock);
SensorManager sensors;



bool radio_init()
{
  rtc_clock.begin(Wire);

#if defined(P_LORA_SCLK)
  spi.begin(P_LORA_SCLK, P_LORA_MISO, P_LORA_MOSI);
  return radio.std_init(&spi);
#else
  return radio.std_init();
#endif

#ifdef RX_BOOSTED_GAIN
    radio.setRxBoostedGainMode(RX_BOOSTED_GAIN);
#endif

    radio.setCRC(1);

    return true; // success
}

mesh::LocalIdentity radio_new_identity()
{
    RadioNoiseListener rng(radio);
    return mesh::LocalIdentity(&rng); // create new random identity
}
