#include <Arduino.h>
#include "Settings.hxx"

Settings defLimits {
  .noiseLower = 10000,
  .noiseUpper = 12000,
  .samplePeriod = 100,   // 100ms
  .reportPeriod = 1000,  // 1s
};

Settings *limits = &defLimits;
