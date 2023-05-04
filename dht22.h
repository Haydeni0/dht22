#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#include <algorithm>
#include <csignal>
#include <iostream>

#define MAX_TIMINGS 85  // Takes 84 state changes to transmit data
#define NBITS 40        // Total number of bits of data
#define BAD_VALUE 999

void twoMeans(const int (&x)[NBITS], bool (&assignUpper)[NBITS]);

class DhtSensor
{
   public:
    int m_pin;
    float m_humidity{BAD_VALUE};
    float m_temperature{BAD_VALUE};

   public:
    DhtSensor(int pin);
    void read();
    
};

