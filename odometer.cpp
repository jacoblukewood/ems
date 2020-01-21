#include "odometer.h"

Odometer::Odometer(unsigned int kEEPROMOdometerAddress) : kEEPROMOdometerAddress_(kEEPROMOdometerAddress), OdometerStart(EEPROM.get(kEEPROMOdometerAddress_, OdometerStart))
{
    // Stored in meters
    OdometerTrip = 0;
}

void Odometer::SaveOdometer()
{
    EEPROM.put(kEEPROMOdometerAddress_, OdometerStart + OdometerTrip);
}

void Odometer::AddOdometer(int value)
{
    OdometerTrip += value;
}

float Odometer::GetOdometer(void)
{
    return (OdometerStart + OdometerTrip) / 1000; // Returns the odometer in km
}