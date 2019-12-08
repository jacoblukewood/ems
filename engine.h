#ifndef ENGINE_H
#define ENGINE_H
#include <Arduino.h>
#include <HardwareSerial.h>

class Engine
{
    private:
        unsigned int const kPinOutputPoints_;
        unsigned int const kPinOutputStarterMotor_;
        unsigned int const kPinInputSensorTachometer_;
        unsigned int const kTimeoutCranking_;
        unsigned int const kTachometerRunningMinimum_;
        unsigned int const kTachometerRedline_;
        unsigned long start_attempt_time_;

    public:
        Engine(unsigned int const kTimeoutCranking, unsigned int const kTachometerRunningMinimum, unsigned int const kTachometerRedline, unsigned int const kPinOutputPoints, unsigned int const kPinOutputStarterMotor, unsigned int const kPinInputSensorTachometer);

        bool Start(void);

        void Stop(void) const;

        bool GetState(void) const;

        unsigned int GetTachometer(const int kPinInputSensorTachometer) const;
};

#endif // ENGINE_H
