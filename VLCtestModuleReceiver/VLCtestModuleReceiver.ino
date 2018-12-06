#include "VLCreceiver.h"
#include <TimerOne.h>
#define SYMBOL_PERIOD 900
#define MESSAGE_LENGTH 8
int voltageSensor = A0;
int THRESHOLD = 38;
String preambleCorrect="111111";
VLCreceiver receiver = VLCreceiver(A0);
int globalCount=1;




void setup() 
{
   // set prescale to 16
  ADCSRA = (ADCSRA & 0xf8) | 0x04; // set 16 times division
   Serial.begin(115200);
   cli();//stop interrupts
   Timer1.initialize(SYMBOL_PERIOD); //1200 bauds
   Timer1.attachInterrupt(receive_half_bit); 
   sei();//allow interrupts
}

void loop() 
{
 
}

void receive_half_bit(){
    int sample=analogRead(A0);
  if(receiver.preambleReceived==false){
    
    if(sample>THRESHOLD){
        receiver.preamble=receiver.preamble.substring(1)+=("1");  
     //   Serial.println(sample);
    }
    else{
      receiver.preamble=receiver.preamble.substring(1)+=("0");
    //  Serial.println(sample);
     }
     
     if(receiver.checkPreamble(preambleCorrect)){
        receiver.preambleReceived=true;
      }

      return;
  }
  //else if(globalCount==1){
  //  globalCount=0;
  //  }
   else if(receiver.preambleReceived==true)
   {
        //Serial.println(sample);
        if(receiver.numSamples<1){
              receiver.prevSample=sample;
              receiver.numSamples=1;
          }
        else{
              int diff=sample-receiver.prevSample;
              receiver.bitsReceived+=1;
              if(diff>0){
                receiver.message=receiver.message+=("1");
                /*
                Serial.print("1  ::");
                Serial.print("Sample 1::");
                Serial.print(receiver.prevSample);
                Serial.print("::Sample2");
                Serial.println(sample);
                */
                
                }
              else{
                 receiver.message=receiver.message+=("0");
                 /*
                   Serial.print("0  ::");
                Serial.print("Sample 1   ");
                Serial.print(receiver.prevSample);
                Serial.print("::  Sample2  ");
                Serial.println(sample);
                */
                }
               
                receiver.numSamples=0;
                if(receiver.bitsReceived==MESSAGE_LENGTH){
                  Serial.println(receiver.message);
                  receiver.bitsReceived=0;
                  receiver.message="";
                  receiver.preambleReceived=false;
                  receiver.preamble="123456";
                }
          
          }
        
        
    
    }
  
  
 }
