#ifndef LOUDNESS_HXX
#define LOUDNESS_HXX

#include <Arduino.h>

namespace loudness {

uint32_t getAvg();
uint32_t getCurrent();
void takeReading();

}
#endif
