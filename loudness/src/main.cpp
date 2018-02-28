#include <Arduino.h>
// #include <EEPROM.h>
#include <Timer.h>
#include <Loudness.hxx>

#if PLTF_STM32
const int analogPin = PA0;
const int ledPin = PC13;
const int dbgPin = PB12;
#else  // default: AVR
const int analogPin = 0;
const int ledPin = 13;
const int dbgPin = 7;
#endif"";

Timer t;
// current reaing (rms)
uint32_t analogVal = 0;
//
// highest noise val has 10 ** 2 bits / 12 ** 2 bits
uint32_t ringBuf[ringSize];


uint32_t getAvg(){
  // AVR:   75µs
  // STM32: 12µs
  uint32_t avg = 0;
  for (int i=0; i < ringSize; i++){
    avg += ringBuf[i];
  }
  return (avg / ringSize);
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

void reportReadings()
{
  static uint32_t noiseAvg = 0;
  noiseAvg = getAvg();
  if (noiseAvg >= limits->noiseUpper) {
    digitalWrite(ledPin, HIGH);
  } else if(noiseAvg <= limits->noiseLower) {
    digitalWrite(ledPin, LOW);
  }
  Serial.print("noise:");
  Serial.print(analogVal);
  Serial.print(":");
  Serial.print(noiseAvg);
  Serial.print(":");
  Serial.print(limits->noiseLower);
  Serial.print(":");
  Serial.println(limits->noiseUpper);
}

inline void doInput(){
  auto command = Serial.readString();
  command.toLowerCase();
  for(uint8_t i=0; callbacks[i].cmd != ""; i++) {
    Serial.println(i);
    digitalWrite(dbgPin, HIGH);
    if (command.startsWith(callbacks[i].cmd)) {
      auto subcmd = command.substring(callbacks[i].cmd.length());
      subcmd.trim();
      callbacks[i].cb(subcmd);

      digitalWrite(dbgPin, LOW);
      return;
    }
  }
  digitalWrite(dbgPin, LOW);

}

void setup() {
  Serial.begin(9600);

  // Setup pins
  pinMode(ledPin, OUTPUT);
  pinMode(dbgPin, OUTPUT);

  // ReadEEPROM
  loadCmd("");

  // Clear ring buffer
  for(int i = 0; i < ringSize; i++){
    ringBuf[i] = 0;
  }
  t.every(limits->samplePeriod, takeReading);
  t.every(limits->reportPeriod, reportReadings);
}

void loop() {
  t.update();
  if (Serial.available() > 0){
    doInput();
  }
}
