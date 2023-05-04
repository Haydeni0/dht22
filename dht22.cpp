
#include "dht22lib.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " pin"
                  << "\n";
        return 1;
    }

    if (wiringPiSetup() == -1) {
        std::cout << "wiringPi setup failed";
        return 1;
    }

    int pin;
    try {
        pin = std::stoi(argv[1]);
    } catch (std::invalid_argument) {
        std::cerr << "Invalid argument: " << argv[1] << "\n";
        return 1;
    }
    DhtSensor sensor{pin};

#ifdef DEBUG
    printf("DEBUG MODE: Displaying microseconds in each state.\n");
    printf("Rows with \033[0;31mRED\033[0m text would have been previously decoded wrongly.\n");
    for (int j{0}; j < NBITS; j++) {
        printf("%3d", j);
        if ((j != 0) && (j % 8 == 7))
            printf("║");
        else
            printf("|");
    }
    std::cout << "\n";
    for (int j{0}; j < NBITS; j++)
        printf("----");
    std::cout << "\n";
#endif

    int delayMilliseconds = 500;
    for (int i = 0; i < 1000; i++) {
        sensor.read();
        switch (sensor.m_readType) {
            case GOOD:
                printf("%-3.1f *C  Humidity: %-3.1f%%\n", sensor.m_temperature, sensor.m_humidity);
                break;
            case BAD:
                printf("Failed checksum\n");
                break;
            case ERROR:
                printf("ERROR, no data read\n");
                break;
            default:
                std::cerr << "This shouldn't happen\n";
                return 1;
        }

        

        delay(delayMilliseconds);  // Wait between readings
    }

    return (0);
}