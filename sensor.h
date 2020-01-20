#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <HardwareSerial.h>
#include "helper.h"

class Sensor
{
public:
    Sensor(int const kPinInput);
    bool GetState(void) const;

private:
    int const kPinInput_;
};

#endif // SENSOR_H
