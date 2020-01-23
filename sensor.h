// Copyright 2020 Jacob Wood

#ifndef SENSOR_H_
#define SENSOR_H_

class Sensor {
 public:
    explicit Sensor(int const kPinInput);

    bool GetState(void) const;

 private:
    int const kPinInput;
};

#endif  // SENSOR_H_
