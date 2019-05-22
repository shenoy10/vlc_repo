//CURRENT VERSION: 04/27/2019
#include "VLCreceiver.h"
#include <TimerOne.h>
#define SYMBOL_PERIOD 400
#define MESSAGE_LENGTH 10
//#define MESSAGE_LENGTH 16
//#define MESSAGE_LENGTH 32
//#define MESSAGE_LENGTH 64
//#define MESSAGE_LENGTH 128
//#define MESSAGE_LENGTH 8

int voltageSensor = A0;
int THRESHOLD = 75;
String preambleCorrect="111111";
VLCreceiver receiver = VLCreceiver(A0);
int globalCount=1;
bool onMessageWhole=false;
int msgCount=0;
String finalMessage=""; 
IntervalTimer myTimer;
int tpin = A9;
int count=0;
void setup() 
{
  //tpin=pinMode(A9,INPUT);
  pinMode(tpin,INPUT);
   // set prescale to 16
  //ADCSRA = (ADCSRA & 0xf8) | 0x04; // set 16 times division
   Serial.begin(115200);
     pinMode(LED_BUILTIN, OUTPUT);
   cli();//stop interrupts
   myTimer.begin(receive_half_bit,SYMBOL_PERIOD); 
   sei();//allow interrupts
}

void loop() 
{
 
}

void receive_half_bit(){
    int sample=analogRead(tpin);
    //Serial.println(sample);
    //delayMicroseconds(40);
  digitalWriteFast(LED_BUILTIN, !digitalReadFast(LED_BUILTIN));
  if(receiver.preambleReceived==false){
   
    if(sample>THRESHOLD){
        receiver.preamble=receiver.preamble.substring(1)+=("1");  
        //Serial.println("1"); 
    }
    else{
      receiver.preamble=receiver.preamble.substring(1)+=("0");
     // Serial.println("0");
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
                  //Serial.println(receiver.message);
                  //delayMicroseconds(50);
                  if(onMessageWhole==false && receiver.message=="1010101010"){
                    
                    onMessageWhole=true;
                    msgCount=0;
                    }
                  else if(onMessageWhole==true && msgCount<16){
                    finalMessage+= receiver.message.substring(1,9);
                    msgCount++;
                    }

                  if(msgCount==16){
                    //uncomment for messages
                    Serial.println(finalMessage);
                    finalMessage="";
                    msgCount=0;
                    onMessageWhole=false;
                    }
                  
                  receiver.bitsReceived=0;
                  receiver.message="";
                  receiver.preambleReceived=false;
                  receiver.preamble="123456";
                }
          
          }
        
        
    
    }
  
  
 }
