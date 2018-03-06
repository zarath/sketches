#ifndef COMMANDS_HXX
#define COMMANDS_HXX

#include <Arduino.h>

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
