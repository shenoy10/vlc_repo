#include "VLCreceiver.h"

VLCreceiver::VLCreceiver(int pinVal)                                     //initialize preamble
{
   this->preamble="123456";
   this->message="";
   this->preambleReceived=false;
   this->voltageSensorPin=pinVal;
   this->numSamples=0;
   this->bitsReceived=0;
}


VLCreceiver::checkPreamble(String pream){                                 //set the preamble
  
  return this->preamble==pream;
  
  }
