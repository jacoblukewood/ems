#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H

#include <Arduino.h>
#include <HardwareSerial.h>
#include "accessory.h"
#include "engine.h"
#include "display.h"
#include "helper.h"
#include "sensor.h"

class Motorcycle
{
public:
    Motorcycle(Engine const &engine, Accessory const &tail_light, unsigned int const kPinInputSensorSpeed, unsigned int const kAutoBrakeDecelerationRate, unsigned int const kEmergencyBrakeDecelerationRate, unsigned int const kTailLightStrobeInterval, Display const &display_dash, unsigned int const kPinOutputPower, Sensor const &sensor_side_stand);

    bool PowerOn(void);
    bool PowerOff(void) const;
    bool GetStatePower(void) const;
    bool GetStateSensorSideStand(void) const;
    bool GetStateSafety(void) const;
    unsigned int GetSpeed(void) const;
    unsigned int GetOdometer(void) const;
    unsigned int SpeedComparison(void) const;
    void AutoBrakeLight(void);
    void EmergencyBrakeStrobe(void);

    unsigned int time_enter_acc_;

private:
    unsigned int const kPinInputSensorSpeed_;
    unsigned int const kAutoBrakeDecelerationRate_;
    unsigned int const kEmergencyBrakeDecelerationRate_;
    unsigned int const kTailLightStrobeInterval_;
    unsigned int const kPinOutputPower_;
    Sensor sensor_side_stand_;

    Display display_dash_;
    Engine engine_;
    Accessory tail_light_;
};

#endif // MOTORCYCLE_H
