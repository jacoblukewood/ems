// Copyright 2020 Jacob Wood

#ifndef ENGINE_H_
#define ENGINE_H_

class Engine  {
 public:
    Engine(unsigned int const kTachometerRedline, unsigned int const kTachometerRunningMinimum, unsigned int const kTimeoutCranking, unsigned int const kPinInputSensorTachometer, unsigned int const kPinOutputPoints, unsigned int const kPinOutputStarterMotor);

    bool GetRedlineState(void) const;
    bool GetState(void) const;
    unsigned int GetTachometer(void) const;
    bool Start(void);
    void Stop(void) const;

 private:
    unsigned int const kPinInputSensorTachometer;
    unsigned int const kPinOutputPoints;
    unsigned int const kPinOutputStarterMotor;
    unsigned int const kTachometerRedline;
    unsigned int const kTachometerRunningMinimum;
    unsigned int const kTimeoutCranking;

    unsigned long start_attempt_time_;
};

#endif  // ENGINE_H_
