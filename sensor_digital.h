// sensor_digital.h
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#ifndef SENSORDIGITAL_H_
#define SENSORDIGITAL_H_

#include "sensor.h"

class SensorDigital : public Sensor {
 public:
    explicit SensorDigital(int const pin_input);

    bool GetState(void) const;
};

#endif  // SENSOR_H_
