#include "VLCtransmitter.h"
#include "FIFO.h"

#define NOP __asm__ __volatile__ ("nop\n\t")

VLCtransmitter::VLCtransmitter(int signalPin)
{
  this->transistorSignalPin = signalPin;
  pinMode(signalPin, OUTPUT);
  digitalWrite(signalPin, LOW);
}


void VLCtransmitter::sendStringToReceiver(String message)
{ 
  //Serial.println("Message Length: " + String(message.length()));

    sendCharacterToReceiver(message);   

}

void VLCtransmitter::sendCharacterToReceiver(String code)
{
  sendByteString(code); 
}

/*
String VLCtransmitter::convertCharacterToByteString(char character)
{
  int asciiValue = character;
  int currentBitIndex = 7;
  String byteString = "00000000";
  while(asciiValue > 0)
  {
    if(asciiValue % 2 == 0)
    {
      byteString[currentBitIndex] = '0'; 
    }
    else
    {
      byteString[currentBitIndex] = '1';
    }
    
    asciiValue /= 2;
    currentBitIndex--;
  }
  return byteString;
}*/

void VLCtransmitter::sendByteString(String byteString)
{
 // sendBit(STARTBIT);
  for(int bitIndex = 0; bitIndex < byteString.length(); bitIndex++)
  {
    char bitToSend = byteString[bitIndex];
    sendBit(bitToSend);
  }
 // sendBit(ENDBIT);
}

void VLCtransmitter::sendBit(char bitToSend)
{
 
   
  if(bitToSend == '1') 
  {
   
    commBuff.push(0);
    commBuff.push(1);
   
  }
  else
  {
    commBuff.push(1);
    commBuff.push(0);
    

  }
 

}

