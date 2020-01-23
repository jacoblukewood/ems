// Copyright 2020 Jacob Wood

#ifndef ODOMETER_H_
#define ODOMETER_H_

class Odometer {
 public:
    explicit Odometer(unsigned int kEEPROMOdometerAddress);

    void AddOdometer(int value);
    float GetOdometer(void);
    void SaveOdometer(void);

 private:
    unsigned int kEEPROMOdometerAddress;
    unsigned int kOdometerStart; // Odometer reading from EEPROM at motorcycle startup.

    unsigned int odometer_trip_;        // Odometer value for the trip, to be added to kOdometerStart and written after > 1 hour and at power down.
};

#endif // ODOMETER_H_
