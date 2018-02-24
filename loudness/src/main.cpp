#include <Arduino.h>
#include <Timer.h>

const int analogPin = 0;
const int ledPin = 13;

const uint32_t noiseLower = 10000;
const uint32_t noiseUpper = 12000;

// maximum is 12bit but no arduino has that much ram
const int ringSize = 64;

const int samplePeriod = 100;  // 100ms
const int reportPeriod = 1000;  // 1s

Timer t;
// current reaing (rms)
uint32_t analogVal = 0;
// highest noise val has 10 ** 2 bits
uint32_t ringBuf[ringSize];

uint32_t getAvg(){
  uint32_t avg = 0;
  for (int i=0; i < ringSize; i++){
    avg += ringBuf[i];
  }
  return (avg / ringSize);
}

void takeReading()
{
  static int ringPos = 0;
  analogVal = 0;

  analogVal = analogRead(analogPin);
  // make square as rms matters
  analogVal *= analogVal;
  ringBuf[ringPos++] = analogVal;
  ringPos %= ringSize;
}

void reportReadings()
{
  static uint32_t noiseAvg = 0;

  noiseAvg = getAvg();

  if (noiseAvg >= noiseUpper) {
    digitalWrite(ledPin, HIGH);
  } else if(noiseAvg <= noiseLower) {
    digitalWrite(ledPin, LOW);
  }
  Serial.print("noise:");
  Serial.print(analogVal);
  Serial.print(":");
  Serial.println(noiseAvg);

}

void setup() {
  Serial.begin(9600);

  // Setup pins
  pinMode(ledPin, OUTPUT);

  // Clear ring buffer
  for(int i = 0; i < ringSize; i++){
    ringBuf[i] = 0;
  }
  t.every(samplePeriod, takeReading);
  t.every(reportPeriod, reportReadings);
}

void loop() {
  t.update();
}
