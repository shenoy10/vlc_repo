#ifndef VLCreceiver_h
#define VLCreceiver_h

#include "Arduino.h"

class VLCreceiver
{

  public:
  static const int standardDelayInMicroseconds = 30000;
  static const char STARTBIT = '1';
  VLCreceiver(int pinVal);
  String preamble;
  bool preambleReceived;
  String message;
  VLCreceiver::checkPreamble(String pream);
  int numSamples;
  int prevSample;
  int bitsReceived;
  
  private:
  int voltageSensorPin;
  int THRESHOLD;
  int currentEnvironmentalNoiseReading;
  int getSensorReading();
  
};


#endif
