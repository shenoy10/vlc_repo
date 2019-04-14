#include "VLCtransmitter.h"
#include "FIFO.h"
#include <TimerOne.h>
#define MESSAGE_LENGTH 16  //2 times actual message length
int transmitterPin = 2;
int on= B00000100;
int off= B11111011;
VLCtransmitter transmitter = VLCtransmitter(transmitterPin);


#define SYMBOL_PERIOD 200000 /* Defined a symbol period in us*/
int first_half=0;
int preambleCount=0;
int messageCount=0;

void setup() 
{  transmitter.commBuff=FIFO();
String ma="";
String message="11010110";
for(int i=0; i<2; i++){
  ma+=message;
  }
  
  transmitter.sendStringToReceiver("11010110");
   Serial.begin(115200);
   cli();                                                               //stop interrupts
   Timer1.initialize(SYMBOL_PERIOD);                                    //1200 bauds
   Timer1.attachInterrupt(emit_half_bit); 
   sei();                                                               //allow interrupts
   
}

void loop() 
{
 

}


void emit_half_bit(){
  if(preambleCount<6){
     PORTD&=off;
      preambleCount++;
    
  }
  else{
     messageCount++;
     if(transmitter.commBuff.sizeOfBuffer()!=0){
        int halfbit=transmitter.commBuff.readBuffer();                   //send the half bits based on light signal
        
        if(halfbit==1 ){      
             PORTD&=off;
        }
        else{
          PORTD|=on;
        }
        
     }
     else{
                                                                         //consistently send high
       
      }
      if(messageCount==MESSAGE_LENGTH){
        preambleCount=0;
        messageCount=0;
        }
  }
}
