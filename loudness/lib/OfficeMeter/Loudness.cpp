#include <Arduino.h>

#include "Settings.hxx"
#include "Loudness.hxx"

namespace loudness {

Loudness::Loudness(const int Pin, const uint8_t RingBufSize):
  pin(Pin), bufsize(RingBufSize) {
  ringbuf = new uint32_t[bufsize];
}

Loudness::~Loudness(){
  delete ringbuf;
}

void Loudness::read(){
  // AVR:   140µs
  // STM32:   8µs
  static uint32_t v;

  v = analogRead(pin);
  val = v;

  if (zerolevel) {
    if (v >= zerolevel)
      v-= zerolevel;
    else
      v = 0;
  }
  // make square as rms matters
  ringbuf[ringpos++] = v * v;
  ringpos %= bufsize;
}

void Loudness::set0level(uint32_t ZeroLevel){
  zerolevel = ZeroLevel;
}

uint32_t Loudness::get() {
  return val;
}

uint32_t Loudness::getSqAvg() {
  // AVR:   75µs
  // STM32: 12µs
  uint32_t avg = 0;
  for (int i=0; i < bufsize; i++){
    avg += ringbuf[i];
  }
  return (avg / bufsize);
}

}
