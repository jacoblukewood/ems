// stand.h
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#ifndef STAND_H_
#define STAND_H_

#include "sensor_digital.h"

class Stand : public SensorDigital {
 public:
    explicit Stand(int const pin_sensor_input);

    bool IsLowered(void) const;
};

#endif  // STAND_H_
