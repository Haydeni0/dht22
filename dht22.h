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

enum DhtReadType{
    GOOD, // Data is read and checksum passes
    BAD, // Data is read and checksum fails
    ERROR, // Attempt to read data, but can't
    NONE, // No attempt to read data
};

class DhtSensor
{
   public:
    int m_pin;
    float m_humidity{BAD_VALUE};
    float m_temperature{BAD_VALUE};
    DhtReadType m_readType{NONE};

   public:
   /**
    * @brief Construct a new DhtSensor object
    * 
    * @param pin wiringPi pin number to read from (run the command ```gpio readall``` to find wPi pin)
    */
    DhtSensor(int pin);

    /**
     * Attempt to read humidity and temperature data from the sensor, and update the member variables
     */
    void read();
    
};

