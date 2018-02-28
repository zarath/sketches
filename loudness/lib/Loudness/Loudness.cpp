#include <Arduino.h>

#include "Loudness.hxx"

Settings defLimits {
  .noiseLower = 10000,
  .noiseUpper = 12000,
  .samplePeriod = 100,   // 100ms
  .reportPeriod = 1000,  // 1s
};

Settings *limits = &defLimits;


void idnCmd(const String &param){
  Serial.println("DG5DBH, Noisemeter, 0001, 0.1");
}

void setCmd(const String &param){
  if (param.startsWith("noiselower:")) {
    auto val = param.substring(11).toInt();
    if (val != 0) limits->noiseLower = (uint32_t) val;
  } else if (param.startsWith("noiseupper:")) {
    auto val = param.substring(11).toInt();
    if (val != 0) limits->noiseUpper = (uint32_t) val;
  } else if (param.startsWith("sampleperiod:")) {
    auto val = param.substring(13).toInt();
    if (val != 0) limits->samplePeriod = (uint32_t) val;
  } else if (param.startsWith("reportperiod:")) {
    auto val = param.substring(13).toInt();
    if (val != 0) limits->reportPeriod = (uint32_t) val;
  }
}

void getCmd(const String &param){
  Serial.print("get:" + param + ":");
  if (param.startsWith("noiselower")) {
    Serial.print(limits->noiseLower);
  } else if (param.startsWith("noiseupper")) {
    Serial.print(limits->noiseUpper);
  }
  Serial.println();
}

void loadCmd(const String &param){

  Serial.println("would load");
  // ReadEEPROM
//  Settings eep;
//  EEPROM.get(0, eep);
//  if (eep.noiseLower == 10000) {
//    limits = &eep;
//  }
}

void saveCmd(const String &param){
  Serial.println("would save");

//  EEPROM.put(0, *limits);
}

void runCmd(const String &param){
  Serial.println("would run");

//  EEPROM.put(0, *limits);
}

void stopCmd(const String &param){
  Serial.println("would stop");

//  EEPROM.put(0, *limits);
}
