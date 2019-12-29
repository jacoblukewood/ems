#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H
#include <Arduino.h>
#include <HardwareSerial.h>

#include "engine.h"
#include "display.h"
#include "helper.h"

class Motorcycle
{
private:
    unsigned int const kPinInputSensorSpeed_;
    unsigned int const kPinInputAdjustmentSpeed_;
    unsigned int const kAutoBrakeDecelerationRate_;
    unsigned int const kEmergencyBrakeDecelerationRate_;
    unsigned int const kTailLightStrobeInterval_;
    unsigned int const kPinOutputPower_;
    unsigned int const kPinInputSensorSideStand_;

    Engine engine_;
    Display display_dash_;

public:
    Motorcycle(Engine &engine, unsigned int const kPinInputSensorSpeed, unsigned int const kPinInputAdjustmentSpeed, unsigned int const kAutoBrakeDecelerationRate, unsigned int const kEmergencyBrakeDecelerationRate, unsigned int const kTailLightStrobeInterval, Display &display_dash, unsigned int const kPinOutputPower, unsigned int const kPinInputSensorSideStand_);

    bool PowerOn(void);

    bool PowerOff(void);

    bool GetStateSensorSideStand(void) const;

    bool GetStateSafety(void) const;

    unsigned int GetSpeed(void) const;

    unsigned int GetOdometer(void) const;
    
    unsigned int SpeedComparison(void) const;

    void AutoBrakeLight(void);

    void EmergencyBrakeStrobe(void);

    unsigned int time_enter_acc_;
};

#endif // MOTORCYCLE_H
