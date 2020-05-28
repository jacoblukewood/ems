// Copyright 2020 Jacob Wood

#ifndef GAUGE_H
#define GAUGE_H

#include <Arduino.h>
#include <Stepper.h>

class Gauge  {
 public:
    Gauge(unsigned int kMotorSteps, unsigned int kMinAngle, unsigned int kMaxAngle, int kPin1, int kPin2, int kPin3, int kPin4);

    void Initialize(unsigned int motorRPM);
    void SetPercentage(unsigned int percentage);
    void SetAngle(unsigned int angle);

 private:
    Stepper stepper;
    unsigned int const kMinAngle = 0;
    unsigned int const kMaxAngle = 315;
    unsigned int const kMotorSteps = 600;
    int position = 0;
};

#endif  // GAUGE_H
