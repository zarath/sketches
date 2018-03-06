#include <Arduino.h>
// #include <EEPROM.h>
#include <Timer.h>
#include <Settings.hxx>
#include <Loudness.hxx>
#include <Commands.hxx>

Timer t;

void reportReadings()
{
  static uint32_t noiseAvg = 0;
  noiseAvg = loudness::getAvg();
  if (noiseAvg >= limits->noiseUpper) {
    digitalWrite(ledPin, HIGH);
  } else if(noiseAvg <= limits->noiseLower) {
    digitalWrite(ledPin, LOW);
  }
  Serial.print("noise:");
  Serial.print(loudness::getCurrent());
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

  t.every(limits->samplePeriod, loudness::takeReading);
  t.every(limits->reportPeriod, reportReadings);
}

void loop() {
  t.update();
  if (Serial.available() > 0){
    doInput();
  }
}
