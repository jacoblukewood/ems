#ifndef ODOMETER_H
#define ODOMETER_H

#include <Arduino.h>
#include <HardwareSerial.h>
#include <EEPROM.h>

class Odometer
{
public:
    Odometer(unsigned int kEEPROMOdometerAddress);
    void SaveOdometer(void);
    void AddOdometer(int value);
    float GetOdometer(void);

private:
    unsigned int const OdometerStart; // Odometer reading from EEPROM at motorcycle startup.
    unsigned int OdometerTrip;        // Odometer value for the trip, to be added to kOdometerStart and written after > 1 hour and at power down.
    unsigned int kEEPROMOdometerAddress_;
};

#endif // ODOMETER_H
