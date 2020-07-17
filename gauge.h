// gauge.h
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#ifndef GAUGE_H
#define GAUGE_H

#include <Arduino.h>
#include <Stepper.h>

class Gauge {
 public:
    Gauge(unsigned int const motor_steps, unsigned int const stepper_rpm, unsigned int const min_angle, unsigned int const max_angle, unsigned int const pin_1, unsigned int const pin_2, unsigned int const pin_3, unsigned int const pin_4);

    void SetPercentage(unsigned int percentage);
    void SetAngle(unsigned int angle);

 private:
    Stepper stepper;
    unsigned int const kStepperRPM;
    unsigned int const kMinAngle;
    unsigned int const kMaxAngle;
    unsigned int const kMotorSteps;
    int current_position_ = 0;
};

#endif  // GAUGE_H
