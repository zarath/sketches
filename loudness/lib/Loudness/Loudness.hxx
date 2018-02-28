#ifndef LOUDNESS_HXX
#define LOUDNESS_HXX

#include <Arduino.h>

// maximum is 12bit but no arduino has that much ram
const int ringSize = 64;

struct Settings {
  uint32_t noiseLower;
  uint32_t noiseUpper;
  uint32_t samplePeriod;
  uint32_t reportPeriod;
  uint16_t chksum;
};

extern Settings defLimits;
extern Settings *limits;

void idnCmd(const String&);
void setCmd(const String&);
void getCmd(const String&);
void loadCmd(const String&);
void saveCmd(const String&);
void runCmd(const String&);
void stopCmd(const String&);

typedef void (*Callback)(const String&) ;
struct CmdCallbacks {
  String cmd;
  Callback cb;
};

const CmdCallbacks callbacks[] = {
  {"*idn?", &idnCmd},
  {":set:", &setCmd},
  {":get:", &getCmd},
  {":load", &loadCmd},
  {":save", &saveCmd},
  {":run", &runCmd},
  {":stop", &stopCmd},
  {"", nullptr},
};

#endif
