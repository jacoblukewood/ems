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

public:
    Motorcycle(Engine &engine, unsigned int const kPinInputSensorSpeed, unsigned int const kPinInputAdjustmentSpeed, unsigned int const kAutoBrakeDecelerationPercentage, unsigned int const kEmergencyBrakeDecelerationPercentage, unsigned int const kTailLightStrobeInterval, Display &display_dash);

    int Start();

    int Stop();

    bool GetRunningState();

    bool GetSensorStandState();

    unsigned int GetSpeed() const;

    void AutoBrakeLight();

    void EmergencyBrakeStrobe();
};

#endif // MOTORCYCLE_H
