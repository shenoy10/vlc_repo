#include "VLCtransmitter.h"
#include "FIFO.h"
#include <TimerOne.h>
//#define MESSAGE_LENGTH 16  //2 times actual message length
//#define MESSAGE_LENGTH 256
//#define MESSAGE_LENGTH 32
//#define MESSAGE_LENGTH 64
//#define MESSAGE_LENGTH 128
//#define MESSAGE_LENGTH 256
//#define MESSAGE_LENGTH 20
#define MESSAGE_LENGTH 20
int transmitterPin = 2;
int on= B00000100;
int off= B11111011;
VLCtransmitter transmitter = VLCtransmitter(transmitterPin);

//900 for 8 bits
//600 for 16 bits
//300 for 32 bits
//200 for 64 bits
#define SYMBOL_PERIOD 5000 /* Defined a symbol period in us*/
//500000 works
int first_half=0;
int preambleCount=0;
int messageCount=0;

void setup() 
{  transmitter.commBuff=FIFO();
   //transmitter.sendStringToReceiver("");
   /*new*/
   String ma="10011001";
   String me="10111101";
   String message="";

   for(int i=0; i<16; i++){
    message+=ma;
   // message+=me;
    }

    //add the extra one's and zeroes
   String final_message="1010101010";
   int indexOrig=0;
    for(int i=0; i<16; i++){
      final_message+=1;
      int indexfin=indexOrig+8;
      while(indexfin>indexOrig){
        final_message+=message[indexOrig];
        indexOrig++;
        }
       final_message+=0;
    }
  
    //last piece of first preamble
    //String message_pream="1010101010";
    //final_message=message_pream.concat(final_message);
   transmitter.sendStringToReceiver(final_message);
   //transmitter.sendStringToReceiver(ma);
  //transmitter.sendStringToReceiver("10100100");
   //new ends here
   Serial.begin(115200);
   //Serial.println(final_message);
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
