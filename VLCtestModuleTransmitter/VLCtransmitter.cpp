#include "VLCtransmitter.h"
#include "FIFO.h"

#define NOP __asm__ __volatile__ ("nop\n\t")

VLCtransmitter::VLCtransmitter(int signalPin)                                 //Initialize all elements
{
  this->transistorSignalPin = signalPin;
  pinMode(signalPin, OUTPUT);
  digitalWrite(signalPin, LOW);
}


void VLCtransmitter::sendStringToReceiver(String message)
{ 
  
    sendCharacterToReceiver(message);                                         //Sends data to reciever

}

void VLCtransmitter::sendCharacterToReceiver(String code)
{
    sendByteString(code);                                                     //Sends String to be sent to the reciever
}


void VLCtransmitter::sendByteString(String byteString)
{
  for(int bitIndex = 0; bitIndex < byteString.length(); bitIndex++)
  {
    char bitToSend = byteString[bitIndex];                                     //Sends message bit by bit
    sendBit(bitToSend);
  }
 
}

void VLCtransmitter::sendBit(char bitToSend)                                    //Send data based on manchester encoding scheme
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
