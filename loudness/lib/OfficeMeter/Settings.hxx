#ifndef SETTINGS_HXX
#define SETTINGS_HXX

#include <Arduino.h>

#if PLTF_STM32
const int analogPin = PA0;
const int ledPin = PC13;
const int dbgPin = PB12;
#else  // default: AVR
const int analogPin = 0;
const int ledPin = 13;
const int dbgPin = 7;
#endif

struct Settings {
  uint32_t noiseLower;
  uint32_t noiseUpper;
  uint32_t samplePeriod;
  uint32_t reportPeriod;
  uint16_t chksum;
};

extern Settings defLimits;
extern Settings *limits;

#endif
