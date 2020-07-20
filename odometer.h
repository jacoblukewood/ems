// odometer.h
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#ifndef ODOMETER_H_
#define ODOMETER_H_

class Odometer {
 public:
    explicit Odometer(unsigned int kEEPROMOdometerAddress);

    void AddMetersToOdometer(float meters_to_add);
    float GetOdometer(void);
    void SaveOdometerToEEPROM(void);

 private:
    unsigned int kEEPROMOdometerAddress;
    unsigned int kOdometerStart; // Odometer reading from EEPROM at motorcycle startup.

    unsigned int meters_traveled_since_last_save_;        // Odometer value for the trip, to be added to kOdometerStart and written after > 1 hour and at power down.
};

#endif // ODOMETER_H_
