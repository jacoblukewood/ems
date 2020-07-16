// engine.h
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#ifndef ENGINE_H_
#define ENGINE_H_

class Engine  {
 public:
    Engine(unsigned int const tachometer_redline, unsigned int const tachometer_running_minimum_rpm, unsigned int const timeout_cranking, unsigned int const pin_input_sensor_tachometer, unsigned int const pin_output_points, unsigned int const pin_output_starter_motor);

    bool IsRedlining(void) const;
    bool IsRunning(void) const;
    unsigned int GetTachometer(void) const;
    void Start(void);
    void Stop(void) const;

 private:
    unsigned int const kPinInputSensorTachometer;
    unsigned int const kPinOutputPoints;
    unsigned int const kPinOutputStarterMotor;
    unsigned int const kTachometerRedline;
    unsigned int const kTachometerRunningMinimumRPM;
    unsigned int const kTimeoutCranking;

    unsigned long start_attempt_time_;
};

#endif  // ENGINE_H_
