/*
 * FIFO Buffer
 */
 
#ifndef __FIFO__
#define __FIFO__

#include "Arduino.h"

//#define FIFO_SIZE 16
//#define FIFO_SIZE 20
//#define FIFO_SIZE 32
//#define FIFO_SIZE 64
//#define FIFO_SIZE 128
//#define FIFO_SIZE 256
//#define FIFO_SIZE 256
#define FIFO_SIZE 340
//#define FIFO_SIZE 320
//#define FIFO_SIZE 160

class FIFO {
  private:
    int head;
    int tail;
    int numElements;
    int reader;
    int buff[FIFO_SIZE];
  public:
    FIFO();
    ~FIFO();
    void push(int data);
    int pop();
    int sizeOfBuffer();
    int readBuffer();
};

#endif
