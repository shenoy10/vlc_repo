/*
 * FIFO Buffer
 */

#include "FIFO.h"

FIFO::FIFO() {                                                   //Initialize all variables
  head = 0;
  tail = 0;
  numElements = 0;
  reader=0;
}

FIFO::~FIFO() {
}

void FIFO::push(int data) {

  
  if(numElements == FIFO_SIZE) {
    return;
  }
  else {
    numElements++;                                                //Increment size

   
    if(numElements > 1) {                                         //Only move the tail if there is more than one element
      tail++;                                                     //Increment tail location

      tail %= FIFO_SIZE;n                                         //Make sure tail is within the bounds of the array
     
    }
  
   buff[tail] = data;                                             //Store data into array
  }
}

int FIFO::pop() {
  if(numElements == 0) {
    return -1;
  }
  else {
    //Decrement size
    numElements--;

    int data = buff[head];

    if(numElements >= 1) {
      head++;                                                      //Move head up one position
      
      head %= FIFO_SIZE;                                           //Make sure head is within the bounds of the array
    }

    return data;
  }
}

int FIFO::sizeOfBuffer() {
  return numElements;
}

int FIFO::readBuffer(){
  int data=buff[reader];

  reader++;
  reader%=FIFO_SIZE;                                              //reads the buffer by storing remainder into the reader
  return data;

  }
