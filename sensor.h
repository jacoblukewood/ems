// sensor.h
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#ifndef SENSOR_H_
#define SENSOR_H_

class Sensor {
 public:
    explicit Sensor(int const pin_input)
    : kPinSensorInput(pin_input)
    { };

 protected:
    int const kPinSensorInput;
};

#endif  // SENSOR_H_
