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

/**
 * @brief A decoder that uses the k-means algorithm (with k=2) to cluster the pulse durations
 *
 * Pulses assigned to the upper cluster represent 1's.
 * The two cluster centroids are initialised at the minimum and maximum of the dataset
 *
 * @param x Input data (pulse durations)
 * @param binaryAssignment Pulse assignments based on input data
 */
void twoMeansDecoder(const int (&x)[NBITS], bool (&binaryAssignment)[NBITS]);

/**
 * @brief Midpoint decoder
 *
 * A decoder that uses the midpoint between the minimum and maximum values of pulse durations
 * to classify whether the pulse represents a 1 or 0
 *
 * @param x Input data (pulse durations)
 * @param binaryAssignment Pulse assignments based on input data
 */
void splitDecoder(const int (&x)[NBITS], bool (&binaryAssignment)[NBITS]);

enum DhtReadType {
    GOOD,   // Data is read and checksum passes
    BAD,    // Data is read and checksum fails
    ERROR,  // Attempt to read data, but failed
    NONE,   // No attempt to read data
};

class DhtSensor
{
   public:
    int m_pin;
    float m_humidity{BAD_VALUE};
    float m_temperature{BAD_VALUE};
    DhtReadType m_readType{NONE};

    int m_signalStateDurations[NBITS];
    bool m_signalData[NBITS];

   public:
    /**
     * @brief Construct a new DhtSensor object
     *
     * @param pin wiringPi pin number to read from (run the command ```gpio readall``` to find wPi
     * pin)
     */
    DhtSensor(int pin);

    /**
     * @brief Attempt to read humidity and temperature data from the sensor, and update the member
     * variables
     */
    void read();

    /**
     * @brief Print formatted temperature and humidity to stdout
     */
    void print();

    static void printSignalTitle();

    void printSignal();
};
