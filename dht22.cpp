/*
Compile with 
    g++ dht22.cpp dht22lib.cpp -lwiringPi -DDEBUG -o dht22.exe
*/


#include "dht22lib.h"

int main(int argc, char *argv[])
{
    // Parse inputs
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " pin"
                  << "\n";
        return 1;
    }
    int pin;
    try {
        pin = std::stoi(argv[1]);
    } catch (std::invalid_argument) {
        std::cerr << "Invalid argument: " << argv[1] << "\n";
        return 1;
    }

    // Set up wiringPi to use the regular GPIO pin numbers (http://wiringpi.com/reference/setup/)
    // These are the ones labelled as BCM, on the map shown with command ```gpio readall```
    if (wiringPiSetupGpio() == -1) {
        std::cout << "wiringPi setup failed";
        return 1;
    }

    DhtSensor sensor{pin};

#ifdef DEBUG
    DhtSensor::printSignalTitle();
#endif

    // Read from the sensor
    int delayMilliseconds = 500;
    for (int i = 0; i < 1000; i++) {
        sensor.read();
#ifdef DEBUG
        sensor.printSignal();
#endif
        sensor.print();

        delay(delayMilliseconds);  // Wait between readings
    }

    return (0);
}