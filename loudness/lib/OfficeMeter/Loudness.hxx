#ifndef LOUDNESS_HXX
#define LOUDNESS_HXX

#include <Arduino.h>

namespace loudness {

class Loudness {
private:
  int pin;
  const uint8_t bufsize;
  uint32_t *ringbuf;
  uint8_t ringpos;
  uint32_t val;
  uint32_t zerolevel;
public:
  Loudness(const int Pin, const uint8_t RingBufSize = 64);
  ~Loudness();
  void read();
  void set0level(uint32_t ZeroLevel);
  uint32_t get();
  uint32_t getSqAvg();
};

}
#endif
