#include "VLCtransmitter.h"
#include "FIFO.h"
#include <TimerOne.h>
#define MESSAGE_LENGTH 16  //2 times actual message length
int transmitterPin = 2;
int on= B00000100;
int off= B11111011;
VLCtransmitter transmitter = VLCtransmitter(transmitterPin);


#define SYMBOL_PERIOD 900 /* Defined a symbol period in us*/
//500000 works
int first_half=0;
int preambleCount=0;
int messageCount=0;

void setup() 
{  transmitter.commBuff=FIFO();
  transmitter.sendStringToReceiver("11010110");
   Serial.begin(115200);
   cli();//stop interrupts
   Timer1.initialize(SYMBOL_PERIOD); //1200 bauds
   Timer1.attachInterrupt(emit_half_bit); 
   sei();//allow interrupts
   
}

void loop() 
{
 

}


void emit_half_bit(){
  if(preambleCount<6){
     //Serial.println("preamble");
     //Serial.println(transmitter.commBuff.sizeOfBuffer());
     // PORTD|=on;
     PORTD&=off;
      preambleCount++;
    
  }
  else{
     messageCount++;
     if(transmitter.commBuff.sizeOfBuffer()!=0){
       //Serial.println(transmitter.commBuff.sizeOfBuffer()); 
        //send the half bits based on light signal
        int halfbit=transmitter.commBuff.readBuffer();
       // Serial.println(transmitter.commBuff.size());
       //Serial.println(halfbit);
        if(halfbit==1 ){      
            //PORTD|=on;
             PORTD&=off;
        }
        else{
          //PORTD&=off;
          PORTD|=on;
        }
        
     }
     else{
        //consistently send high
        //digitalWrite(transmitterPin,HIGH);
      }
      if(messageCount==MESSAGE_LENGTH){
        preambleCount=0;
        messageCount=0;
        }
  }
}
