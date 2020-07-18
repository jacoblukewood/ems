// Copyright 2020 Jacob Wood

#ifndef MOTORCYCLE_H_
#define MOTORCYCLE_H_

#include "accessory.h"
#include "button.h"
#include "button_indicator.h"
#include "button_toggle.h"
#include "display.h"
#include "engine.h"
#include "gauge.h"
#include "indicator.h"
#include "light.h"
#include "odometer.h"
#include "rfid_reader.h"
#include "sensor.h"
#include "stand.h"

#include "utility.h"

class Motorcycle {
 public:
    Motorcycle(void);

    void PowerOn(void);
    void PowerOff(void);
    bool IsPoweredOn(void) const;
    bool IsSafeToRide(void) const;
    unsigned int GetSpeed(void) const;
    unsigned int GetOdometer(void) const;
    unsigned int GetPowerOnTime(void) const;
    unsigned int GetAccessoryModeTimeout(void) const;
    void SetPowerOnTime(int new_time_value);

    void RefreshButtons(void);




   //  void AutoBrakeLight(void);
   //  void EmergencyBrakeStrobe(void);
   //  unsigned int SpeedComparison(void) const;


   // Objects
      Accessory horn_;

      Button button_brake_;
      ButtonToggle button_highbeam_;
      Button button_horn_;
      ButtonIndicator button_indicator_left_;
      ButtonIndicator button_indicator_right_;
      // Button button_power_;

      Display display_dash_;

      Engine engine_;

      Gauge gauge_dash_;

      Indicator indicator_left_;
      Indicator indicator_right_;

      Light light_headlight_;
      Light light_tail_;

      Odometer odometer_;

      RFIDReader rfid_reader_;

      Sensor sensor_neutral_;
      Sensor sensor_speed_;

      Stand side_stand_;


 private:
   unsigned int power_on_time_;


   // Pins
      // Accessories
         // Horn
         unsigned int const kPinOutputHorn = 11;

      // Inputs
         // Buttons
            // High Beam
               unsigned int const kPinInputButtonHighBeam = 6;

            // Horn
               unsigned int const kPinInputButtonHorn = 5;

            // Indicators
               // Left
                  unsigned int const kPinInputButtonIndicatorLeft = 2;

               // Right
                  unsigned int const kPinInputButtonIndicatorRight = 3;

            // Power
            unsigned int const kPinInputButtonPower = 4;

            // Rear Brake
               unsigned int const kPinInputButtonRearBrake = 7;

         // RFID
            unsigned int const kPinInputPinSS = 53;
            unsigned int const kPinInputRST = 5;

         // Sensors
            // Engine Tachometer
               unsigned int const kPinInputSensorTachometer = A0;

            // Gearbox Neutral
               unsigned int const kPinInputSensorNeutral = 14;

            // Gearbox Output Speed
               unsigned int const kPinInputSensorSpeed = A1;

            // Side Stand Position
               unsigned int const kPinInputSensorSideStand = 15;


      // Outputs
         // Display
            unsigned int const kPinOutputDisplaySCL = 21;
            unsigned int const kPinOutputDisplaySDA = 20;

         // Engine
            unsigned int const kPinOutputPoints = 14;
            unsigned int const kPinOutputStarterMotor = 15;

         // Gauge
            unsigned int const kPinGaugeDash1 = 1;
            unsigned int const kPinGaugeDash2 = 2;
            unsigned int const kPinGaugeDash3 = 3;
            unsigned int const kPinGaugeDash4 = 4;

         // Headlight
            unsigned int const kPinOutputHeadlight = 12;
            unsigned int const kPinOutputHighBeam = 13;

         // Indicator
            unsigned int const kPinOutputIndicatorLeft = 8;
            unsigned int const kPinOutputIndicatorRight = 9;

         // Motorcycle
            unsigned int const kPinElectronicsPower = 10;

         // Odometer
            unsigned int const kEEPROMOdometerAddress = 0;

         // Tail Light
            unsigned int const kPinOutputTailLight = A6;


   // Configuration
      // Buttons
         // Power
            static unsigned int const kOffHoldTime = 5000;  // Time in milliseconds to hold the power button to trigger it. // TODO: Should this be in the button class?
      // Engine
         unsigned int const kTachometerRedline = 8000;  // RPM value at which the motorcycle meets redline.
         float const kTachometerRunningMinimum = 700.0;  // RPM value at which the engine is determined to have started.
         unsigned int const kTimeoutCranking = 2000;  // Timeout in milliseconds for auto start.

      // Gauges
         unsigned int const kGaugeDashStepperMotorSteps = 300;
         unsigned int const kGaugeDashStepperMotorRPM;
         unsigned int const kGaugeDashMinAngle = 60;
         unsigned int const kGaugeDashMaxAngle = 300;

      // Headlight
         unsigned int const kBrightnessHeadlight = 200;
         unsigned int const kBrightnessHighbeam = 255;

      // Indicator
         float const kAutoOffIndicatorOffMinSpeed = 25.0;  // Speed that the bike must be above for > kAutoOffIndicatorOffTimeout for the indicators to be turned off automatically.
         float const kAutoOffIndicatorOffTimeout = 10.0;  // Time in seconds the indicators must be left on while the bike is travling above kAutoOffIndicatorOffMinSpeed to be automatically turned off.
         unsigned int const kFlashRate = 120;  // Times per minute to flash indicators. (6.3.11.1.1. the light flashing frequency shall be 90 ± 30 times per minute; - Vehicle Standard (Australian Design Rule 19/00 – Installation of Lighting and Light-Signalling Devices on L-Group Vehicles) 2006).
      
      // Motorcycle
         float const kAutoBrakeDecelerationRate = 0.04;  // Decelleration rate in m/s2 that auto brake is activated at/above.
         float const kEmergencyBrakeDecelerationRate = 6.0;  // Deceleration rate in m/s2 that the emergency brake lights are activated at/above. (5.2.23.1. The signal shall not be activated when the vehicle deceleration is below 6 m/s² but it may be generated at any deceleration at or above this value, the actual value being defined by the vehicle manufacturer. - Vehicle Standard (Australian Design Rule 31/04 – Brake Systems for Passenger Cars) 2017).
         unsigned int const kAccessoryModeTimeout = 10000;  // Timeeout in milliseconds to leave accessory mode and power off.

      // Tail Light
         unsigned int const kBrightnessTailLight = 20;  // Tail light (when not activated as a brake light) brightness. Value between 0 (off) - 255 (high, avoid as this is the break light brightness).
         unsigned int const kBrightnessBrakeLight = 255;
         unsigned int const kTailLightStrobeInterval = 100;  // Time in milliseconds between on/off strobe.
};

#endif  // MOTORCYCLE_H_
