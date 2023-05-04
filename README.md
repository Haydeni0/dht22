# Robust Adafruit DHT22 sensor reader

## Why is this "robust"?

This is an improvement on a [previous implementation](http://www.uugear.com/portfolio/read-dht1122-temperature-humidity-sensor-from-raspberry-pi/).

In the previous implementation, the data
(5 bytes: 2 each for humidity/temperature and 1 for a checksum)
is decoded by classifying signal states as ```1``` or ```0``` depending if the duration held by the state is
longer than 16 microseconds or not.

Sometimes, this classification is inaccurate and we get bad data, which is typically
invalidated by the checksum. To see why, here is realistic example of recorded state durations in
microseconds (1 byte only):

             Signal A: ( 3, 2, 3, 8, 8, 9, 8, 3)
             Signal B: ( 7, 7, 7,32,33,33,32, 6)
             Signal C: (21,22,22,86,84,84,85,23)
    True decoded data: ( 0, 0, 0, 1, 1, 1, 1, 0)

It is clear to see that the encoded data is present in all signals, but with the previous
classification technique only signal B will be decoded correctly. I'm not sure exactly why
in some circumstances the state durations are longer/shorter. I've observed consistently
shorter durations when running this in a docker container.

The newer the decoding technique uses k-means (k=2) to cluster the signal into upper and lower
clusters and classify any states assigned to the upper cluster as a ```1```. This results in all
signals A, B and C being decoded correctly.

Other changes:

- Fix undefined behaviour when reading too many bits in the read loop

## Installation

---

### Install wiringPi

Install wiringPi to be able to interface with Raspberry Pi GPIO pins

    git clone https://github.com/WiringPi/WiringPi.git WiringPi
    cd WiringPi
    ./build

---

### Find the ```wPi``` pin your DHT22 is connected to

Look at wiringPi's pin numbers

    gpio readall

Map the ```Physical``` pin, on your Raspberry Pi that the DHT22 data line is connected to, to the ```wPi``` pin.

---

### Compile and run

Define the pin to use at compile time using the option ```-DPIN```. For example, I'm using ```wPi``` pin 25.

    g++ dht22.cpp -lwiringPi -Wall -DPIN=25 -o dht22.exe

To view the debug table showing the results of the robust decoder (read the comments in [dht22.cpp](./dht22.cpp) file for more info), use the ```-DDEBUG``` option.

    g++ dht22.cpp -lwiringPi -Wall -DPIN=25 -DDEBUG -o dht22.exe
