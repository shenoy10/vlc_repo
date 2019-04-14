/*
 * FIFO Buffer
 */
 
#ifndef __FIFO__
#define __FIFO__

#include "Arduino.h"

#define FIFO_SIZE 16

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
