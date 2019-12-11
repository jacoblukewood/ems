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
    unsigned int const kPinInputSensorSpeed_;
    unsigned int const kPinInputAdjustmentSpeed_;
    unsigned int const kAutoBrakeDecelerationPercentage_;
    unsigned int const kEmergencyBrakeDecelerationPercentage_;
    unsigned int const kTailLightStrobeInterval_;
    unsigned int const kPinOutputPower_;

    Engine engine_;
    Display display_dash_;

public:
    Motorcycle(Engine &engine, unsigned int const kPinInputSensorSpeed, unsigned int const kPinInputAdjustmentSpeed, unsigned int const kAutoBrakeDecelerationPercentage, unsigned int const kEmergencyBrakeDecelerationPercentage, unsigned int const kTailLightStrobeInterval, Display &display_dash, unsigned int const kPinOutputPower);

    int PowerOn();

    int PowerOff();

    bool GetSensorStandState();

    bool GetSafetyState();

    unsigned int GetSpeed() const;
    
    unsigned int SpeedComparison();

    void AutoBrakeLight();

    void EmergencyBrakeStrobe();

    unsigned int time_enter_acc_;
};

#endif // MOTORCYCLE_H
