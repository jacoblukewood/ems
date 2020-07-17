// Copyright 2020 Jacob Wood

#ifndef MOTORCYCLE_H_
#define MOTORCYCLE_H_

#include "button.h"
#include "display.h"
#include "engine.h"
#include "indicator.h"
#include "light.h"
#include "odometer.h"
#include "rfid_reader.h"
#include "sensor.h"
#include "gauge.h"
#include "stand.h"

class Motorcycle {
 public:
    Motorcycle();

    void AutoBrakeLight(void);
    void EmergencyBrakeStrobe(void);
    unsigned int GetOdometer(void) const;
    unsigned int GetSpeed(void) const;
    bool IsPoweredOn(void) const;
    bool IsSafeToRide(void) const;
    bool IsSideStandLowered(void) const;
    unsigned int GetPowerOnTime(void) const;
    void PowerOn(void);
    void PowerOff(void);
    unsigned int SpeedComparison(void) const;
    void SetPowerOnTime(int new_time_value);

    Accessory horn_;

    Button button_brake_;
    Button button_highbeam_;
    Button button_horn_;
    Button button_indicator_left_;
    Button button_indicator_right_;
    Button button_power_;

    Display display_dash_;  // TODO: Figure out how to move this down below, but it is needed in the Motorcycle object below. Maybe move these to header file?

    Engine engine_;

    Indicator indicator_left_;
    Indicator indicator_right_;

    Light light_headlight_;
    Light light_tail_;

    Odometer odometer_;

    RFIDReader rfid_seat_;

    Sensor sensor_neutral_;
    Sensor sensor_speed_;
    Sensor sensor_tachometer_;
    
   Stand side_stand;

 private:
    // Accessory
    unsigned int const kPinOutputHorn = 11;

    // Button
    unsigned int const kPinInputButtonBrake = 7;
    unsigned int const kPinInputButtonHighBeam = 6;
    unsigned int const kPinInputButtonHorn = 5;
    unsigned int const kPinInputButtonIndicatorLeft = 2;
    unsigned int const kPinInputButtonIndicatorRight = 3;
    unsigned int const kPinInputButtonPower = 4;

    // Display
    unsigned int const kPinOutputDisplaySCL = 21;
    unsigned int const kPinOutputDisplaySDA = 20;

    // Engine
    unsigned int const kPinOutputPoints = 14;
    unsigned int const kPinOutputStarterMotor = 15;
    unsigned int const kTachometerRedline = 8000;  // RPM value at which the motorcycle meets redline.
    float const kTachometerRunningMinimum = 700.0;  // RPM value at which the engine is determined to have started.
    unsigned int const kTimeoutCranking = 2000;  // Timeout in milliseconds for auto start.

    // Headlight
    unsigned int const kBrightnessHeadlight = 200;
    unsigned int const kBrightnessHighbeam = 255;
    unsigned int const kPinOutputHeadlight = 12;
    unsigned int const kPinOutputHighBeam = 13;

    // Indicator
    float const kAutoOffIndicatorOffMinSpeed = 25.0;  // Speed that the bike must be above for > kAutoOffIndicatorOffTimeout for the indicators to be turned off automatically.
    float const kAutoOffIndicatorOffTimeout = 10.0;  // Time in seconds the indicators must be left on while the bike is travling above kAutoOffIndicatorOffMinSpeed to be automatically turned off.
    unsigned int const kFlashRate = 120;  // Times per minute to flash indicators. (6.3.11.1.1. the light flashing frequency shall be 90 ± 30 times per minute; - Vehicle Standard (Australian Design Rule 19/00 – Installation of Lighting and Light-Signalling Devices on L-Group Vehicles) 2006).
    unsigned int const kPinOutputIndicatorLeft = 8;
    unsigned int const kPinOutputIndicatorRight = 9;

    // Motorcycle
    float const kAutoBrakeDecelerationRate = 0.04;  // Decelleration rate in m/s2 that auto brake is activated at/above.
    float const kEmergencyBrakeDecelerationRate = 6.0;  // Deceleration rate in m/s2 that the emergency brake lights are activated at/above. (5.2.23.1. The signal shall not be activated when the vehicle deceleration is below 6 m/s² but it may be generated at any deceleration at or above this value, the actual value being defined by the vehicle manufacturer. - Vehicle Standard (Australian Design Rule 31/04 – Brake Systems for Passenger Cars) 2017).
    unsigned int const kPinElectronicsPower = 10;
    unsigned int const kAccessoryModeTimeout = 10000;  // Timeeout in milliseconds to leave accessory mode and power off.

    // Odometer
    unsigned int const kEEPROMOdometerAddress = 0;

    // RFID
    unsigned int const kPinInputPinSS = 53;
    unsigned int const kPinInputRST = 5;

    // Sensor
    unsigned int const kPinInputSensorNeutral = 14;
    unsigned int const kPinInputSensorSpeed = A1;
    unsigned int const kPinInputSensorSideStand = 15;
    unsigned int const kPinInputSensorTachometer = A0;

    // Tail Light
    unsigned int const kBrightnessTailLight = 20;  // Tail light (when not activated as a brake light) brightness. Value between 0 (off) - 255 (high, avoid as this is the break light brightness).
    unsigned int const kBrightnessBrakeLight = 255;
    unsigned int const kPinOutputTailLight = A6;
    unsigned int const kTailLightStrobeInterval = 100;  // Time in milliseconds between on/off strobe.

    unsigned int power_on_time_;



    byte const kRFIDKeyList[][4] = {  // List of RFID key UIDs in hex.
      {0xF9, 0xAC, 0x41, 0xC2},
      {0xF9, 0xAC, 0x41, 0xC2}
   };


static unsigned int const kOffHoldTime = 5000;  // Time in milliseconds to hold the power button to trigger it. // TODO: Should this be in the button class?
};

#endif  // MOTORCYCLE_H_
