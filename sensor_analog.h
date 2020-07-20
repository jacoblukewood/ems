// sensor_analog.h
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#ifndef SENSORANALOG_H_
#define SENSORANALOG_H_

#include "sensor.h"

class SensorAnalog : public Sensor {
 public:
    explicit SensorAnalog(int const pin_input);

    double GetValue(void) const;
};

#endif  // SENSOR_H_
