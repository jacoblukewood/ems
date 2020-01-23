#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H

#include <Arduino.h>
#include <HardwareSerial.h>
#include "engine.h"
#include "odometer.h"
#include "accessory.h"
#include "indicator.h"
#include "display.h"
#include "light.h"
#include "sensor.h"
#include "helper.h"
#include "button.h"
#include "rfid.h"

class Motorcycle
{
public:
    Motorcycle();
    void PowerOn(void);
    void PowerOff(void);
    bool GetStatePower(void) const;
    bool GetStateSensorSideStand(void) const;
    bool GetStateSafety(void) const;
    unsigned int GetSpeed(void) const;
    unsigned int GetOdometer(void) const;
    unsigned int GetTimeEnterAccessory(void) const;
    void UpdateTimeEnterAccessory(void);
    unsigned int SpeedComparison(void) const;
    void AutoBrakeLight(void);
    void EmergencyBrakeStrobe(void);

    // Output
    Engine engine_;
    // Display
    Display display_dash_; // TODO: Figure out how to move this down below, but it is needed in the Motorcycle object below. Maybe move these to header file?
    // Accessory
    Accessory horn_;
    // Light
    Light light_tail_;
    Light light_headlight_;
    // Indicator
    Indicator indicator_left_;
    Indicator indicator_right_;

    // Input
    // RFID
    RFID rfid_seat_;
    // Odometer
    Odometer odometer_;
    // Button
    Button button_indicator_left_;
    Button button_indicator_right_;
    Button button_horn_;
    Button button_highbeam_;
    Button button_brake_;
    Button button_power_;
    // Sensor
    // Analog
    Sensor sensor_neutral_;
    Sensor sensor_side_stand_;
    // Digital
    Sensor sensor_tachometer_;
    Sensor sensor_speed_;

private:
    // Variables
    // Motorcycle
    unsigned int time_enter_accessory_;

    // Constants
    // Output
    // Motorcycle
    unsigned int const kPinOutputPower_ = 10;
    float const kAutoBrakeDecelerationRate_ = 0.04;     // Decelleration rate in m/s2 that auto brake is activated at/above.
    float const kEmergencyBrakeDecelerationRate_ = 6.0; // Deceleration rate in m/s2 that the emergency brake lights are activated at/above. (5.2.23.1. The signal shall not be activated when the vehicle deceleration is below 6 m/s² but it may be generated at any deceleration at or above this value, the actual value being defined by the vehicle manufacturer. - Vehicle Standard (Australian Design Rule 31/04 – Brake Systems for Passenger Cars) 2017).
    // Engine
    unsigned int const kPinOutputPoints_ = 14;
    unsigned int const kPinOutputStarterMotor_ = 15;
    unsigned int const kTachometerRedline_ = 8000;  // RPM value at which the motorcycle meets redline.
    unsigned int const kTimeoutCranking_ = 2000;    // Timeout in milliseconds for auto start.
    float const kTachometerRunningMinimum_ = 700.0; // RPM value at which the engine is determined to have started.
    // Display
    unsigned int const kPinOutputDisplaySDA_ = 20;
    unsigned int const kPinOutputDisplaySCL_ = 21;
    // Accessory
    unsigned int const kPinOutputHorn_ = 11;
    // Headlight
    unsigned int const kPinOutputHeadlight_ = 12;
    unsigned int const kPinOutputHighBeam_ = 13;
    unsigned int const kBrightnessHeadlight_ = 200;
    unsigned int const kBrightnessHighbeam_ = 255;
    // Tail Light
    unsigned int const kPinOutputTailLight_ = A6;
    unsigned int const kBrightnessTailLight_ = 20; // Tail light (when not activated as a brake light) brightness. Value between 0 (off) - 255 (high, avoid as this is the break light brightness).
    unsigned int const kBrightnessBrakeLight_ = 255;
    unsigned int const kTailLightStrobeInterval_ = 100; // Time in milliseconds between on/off strobe.
    // Indicator
    unsigned int const kPinOutputIndicatorLeft_ = 8;
    unsigned int const kPinOutputIndicatorRight_ = 9;
    float const kAutoOffIndicatorOffMinSpeed_ = 25.0; // Speed that the bike must be above for > kAutoOffIndicatorOffTimeout for the indicators to be turned off automatically.
    float const kAutoOffIndicatorOffTimeout_ = 10.0;  // Time in seconds the indicators must be left on while the bike is travling above kAutoOffIndicatorOffMinSpeed to be automatically turned off.
    unsigned int const kFlashRate_ = 120;             // Times per minute to flash indicators. (6.3.11.1.1. the light flashing frequency shall be 90 ± 30 times per minute; - Vehicle Standard (Australian Design Rule 19/00 – Installation of Lighting and Light-Signalling Devices on L-Group Vehicles) 2006).
    
    // Input
    // RFID
    unsigned int const kPinInputPinSS_ = 53;
    unsigned int const kPinInputRST_ = 5;
    // Odometer
    unsigned int const kEEPROMOdometerAddress_ = 0;
    // Button
    unsigned int const kPinInputButtonIndicatorLeft_ = 2;
    unsigned int const kPinInputButtonIndicatorRight_ = 3;
    unsigned int const kPinInputButtonHorn_ = 5;
    unsigned int const kPinInputButtonHighBeam_ = 6;
    unsigned int const kPinInputButtonBrake_ = 7;
    unsigned int const kPinInputButtonPower_ = 4;
    // Sensor
    // Analog
    unsigned int const kPinInputSensorSpeed_ = A1;
    unsigned int const kPinInputSensorTachometer_ = A0;
    // Digital
    unsigned int const kPinInputSensorNeutral_ = 14;
    unsigned int const kPinInputSensorSideStand_ = 15;
};

#endif // MOTORCYCLE_H
