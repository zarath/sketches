#include <Arduino.h>

#include "Settings.hxx"
#include "Loudness.hxx"

namespace loudness {

// maximum is 12bit but no arduino has that much ram
const int ringSize = 64;

// highest noise val has 10 ** 2 bits / 12 ** 2 bits
static uint32_t ringBuf[ringSize] = {};

//
uint32_t analogVal = 0;

uint32_t getAvg(){
  // AVR:   75µs
  // STM32: 12µs
  uint32_t avg = 0;
  for (int i=0; i < ringSize; i++){
    avg += ringBuf[i];
  }
  return (avg / ringSize);
}

uint32_t getCurrent(){
  return analogVal;
}

void takeReading()
{
  // AVR:   140µs
  // STM32:   8µs
  static int ringPos = 0;

  analogVal = analogRead(analogPin);
  // make square as rms matters
  analogVal *= analogVal;
  ringBuf[ringPos++] = analogVal;
  ringPos %= ringSize;
}

}
