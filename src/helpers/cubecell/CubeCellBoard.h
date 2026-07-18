#pragma once

#include <MeshCore.h>
#include <Arduino.h>

class CubeCellBoard : public mesh::MainBoard {
protected:
  uint8_t startup_reason;

public:
  virtual void begin() {
    startup_reason = BD_STARTUP_NORMAL;
    pinMode(PIN_ANT_ENABLE,OUTPUT);
    digitalWrite(PIN_ANT_ENABLE,1);
  }

  uint8_t getStartupReason() const override { return startup_reason; }

  uint16_t getBattMilliVolts() override {
    return getBatteryVoltage();  // not supported
  }

  const char* getManufacturerName() const override {
    return "Generic CubeCell";
  }

  void reboot() override {
    //TODO
  }

  void powerOff() override {
    //TODO
  }

#if defined(P_LORA_TX_LED)
  void onBeforeTransmit() override {
    digitalWrite(P_LORA_TX_LED, LOW);   // turn TX LED on
    //digitalWrite(PIN_ANT_ENABLE,1);
  }
  void onAfterTransmit() override {
    digitalWrite(P_LORA_TX_LED, HIGH);   // turn TX LED off
    //digitalWrite(PIN_ANT_ENABLE,0);
  }
#endif

  bool startOTAUpdate(const char* id, char reply[]) override { return false; };
};