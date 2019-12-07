#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H
#include <Arduino.h>
#include <HardwareSerial.h>

#include "engine.h"
#include "display.h"
#include "utility.h"

class Motorcycle
{
private:
    Engine engine_;
    unsigned int const kPinInputSensorSpeed_;
    unsigned int const kPinInputAdjustmentSpeed_;
    unsigned int const kAutoBrakeDecelerationPercentage_;
    unsigned int const kEmergencyBrakeDecelerationPercentage_;
    unsigned int const kTailLightStrobeInterval_;
    Display display_dash_;
    unsigned int const kPinOutputPower_;

public:
    Motorcycle(Engine &engine, unsigned int const kPinInputSensorSpeed, unsigned int const kPinInputAdjustmentSpeed, unsigned int const kAutoBrakeDecelerationPercentage, unsigned int const kEmergencyBrakeDecelerationPercentage, unsigned int const kTailLightStrobeInterval, Display &display_dash, unsigned int const kPinOutputPower);

    int On();

    int Off();

    bool GetSensorStandState();

    bool GetSafetyState();

    unsigned int GetSpeed() const;

    void AutoBrakeLight();

    void EmergencyBrakeStrobe();

    void PowerButton();

    unsigned int engine_stop_time_;
};

#endif // MOTORCYCLE_H
