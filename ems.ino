// ems.ino - BMW R80 electronics management system.
// Written 2019 by Jacob Wood.

#include <Arduino.h>
#include <EEPROM.h>
#include <HardwareSerial.h>
#include "motorcycle.h"
#include "engine.h"
#include "accessory.h"
#include "indicator.h"
#include "display.h"
#include "light.h"
#include "helper.h"
#include "button.h"
#include "rfid.h"

// Constants
static float const kTachometerRunningMinimum = 10.0; // * CONFIGURABLE * An RPM value which is below the lowest RPM the engine could hit when running but well above the RPM the engine could hit when the start motor is running.
static float const kAutoBrakeDecelerationRate = 0.04; // * CONFIGURABLE *
static float const kEmergencyBrakeDecelerationRate = 6.0; // * CONFIGURABLE * Deceleration ate in m/s that the emergency brake lights are activated. (5.2.23.1. The signal shall not be activated when the vehicle deceleration is below 6 m/s² but it may be generated at any deceleration at or above this value, the actual value being defined by the vehicle manufacturer. - Vehicle Standard (Australian Design Rule 31/04 – Brake Systems for Passenger Cars) 2017).
static unsigned int const kTimeoutCranking = 2000; // * CONFIGURABLE * The amount of milliseconds to run the start motor before timing out if the engine has not started.
static unsigned int const kOffHoldTime = 5000; // * CONFIGURABLE * The length of time in milliseconds the start button should be held to turn the engine off.
static unsigned int const kFlashRate = 120; // * CONFIGURABLE * Times per minute to flash indicators. (6.3.11.1.1. the light flashing frequency shall be 90 ± 30 times per minute; - Vehicle Standard (Australian Design Rule 19/00 – Installation of Lighting and Light-Signalling Devices on L-Group Vehicles) 2006).
static unsigned int const kTailLightBrightness = 20; // * CONFIGURABLE * A brightness value between 0 and 255 to be used for the  tail light brightness when the break light is off.
static unsigned int const kTachometerRedline = 8000; // * CONFIGURABLE *
static unsigned int const kTailLightStrobeInterval = 100; // * CONFIGURABLE * Milliseconds between on/off strobe.
static unsigned int const kKey = 123;
static unsigned int const kTimeAutoOff = 10000;
static unsigned long const kOdometerStart;

// Variables
static unsigned long OdometerTrip = 0;

// Pins
// Outputs
// Buttons
static unsigned int const kPinOutputIndicatorLeft = 8;
static unsigned int const kPinOutputIndicatorRight = 9;
static unsigned int const kPinOutputPower = 10;
static unsigned int const kPinOutputHorn = 11;
static unsigned int const kPinOutputHeadlight = 12;
static unsigned int const kPinOutputHighBeam = 13;
static unsigned int const kPinOutputTailLight = A6;

// Engine
static unsigned int const kPinOutputPoints = 14;
static unsigned int const kPinOutputStarterMotor = 15;

// Display
static unsigned int const kPinOutputDisplaySDA = 20;
static unsigned int const kPinOutputDisplaySCL = 21;

// Inputs
// Buttons
static unsigned int const kPinInputButtonIndicatorLeft = 2;  // Right Indicator Button - TOGGLE
static unsigned int const kPinInputButtonIndicatorRight = 3; // Left Indicator Button - TOGGLE
static unsigned int const kPinInputButtonPower = 4;          // Start Button - MOMENTARY
static unsigned int const kPinInputButtonHorn = 5;           // Horn Button - MOMENTARY
static unsigned int const kPinInputButtonHighBeam = 6;       // High Beam Button - TOGGLE
static unsigned int const kPinInputButtonBrake = 7;          // Brake Light Button - MOMENTARY

// Sensors
static unsigned int const kPinInputSensorTachometer = A0; // Tachometer Analogue Input
static unsigned int const kPinInputSensorSpeed = A1;      // Speedometer Digital Input - Must be a valid interrupt pin (https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)
static unsigned int const kPinInputSensorNeutral = A2;
static unsigned int const kPinInputSensorSideStand = A3;

// Adjustments
static unsigned int const kPinInputAdjustmentSpeed = A5;

// Objects
// Outputs
Engine engine(kTimeoutCranking, kTachometerRunningMinimum, kTachometerRedline, kPinOutputPoints, kPinOutputStarterMotor, kPinInputSensorTachometer);
Display display_dash;
Motorcycle motorcycle(engine, kPinInputSensorSpeed, kPinInputAdjustmentSpeed, kAutoBrakeDecelerationRate, kEmergencyBrakeDecelerationRate, kTailLightStrobeInterval, display_dash, kPinOutputPower, kPinInputSensorSideStand);

// Accessories
Indicator indicator_left(kPinOutputIndicatorLeft, kFlashRate, motorcycle);
Indicator indicator_right(kPinOutputIndicatorRight, kFlashRate, motorcycle);
Accessory horn(kPinOutputHorn);
Light headlight(kPinOutputHeadlight, kPinOutputHighBeam);
Light tail_light(kPinOutputTailLight, kTailLightBrightness);
Button button_indicator_left(kPinInputButtonIndicatorLeft, &indicator_left, Button::ButtonTypes::kToggle);
Button button_indicator_right(kPinInputButtonIndicatorRight, &indicator_right, Button::ButtonTypes::kToggle);
Button button_horn(kPinInputButtonHorn, &horn, Button::ButtonTypes::kMomentary);
Button button_highbeam(kPinInputButtonHighBeam, &headlight, Button::ButtonTypes::kToggle);
Button button_brake(kPinInputButtonBrake, &tail_light, Button::ButtonTypes::kMomentary);
Button button_power(kPinInputButtonPower, &motorcycle, Button::ButtonTypes::kPower);
RFID rfid(kKey);

void setup()
{
  display_dash.Setup();

  // Wait for valid key. The reed switch will keep the power on for this time, turning off if a key is removed.
  while(!rfid.Verify())
  {
    display_dash.PrintLnCenter("Invalid Key", 0);
  }

  // Permanently Power on EMU. Accessory mode.
  motorcycle.PowerOn();
  display_dash.PrintLnCenter("Ready", 0);
}

void loop()
{
  // If engine is running.
  if (engine.GetState())
  {
    // If power button is pressed.
    if (button_power.GetState()) {
      engine.Stop();
      motorcycle.time_enter_acc_ = millis();
    }
    // If it is unsafe.
    if (motorcycle.GetStateSafety()) {
      engine.Stop();
      motorcycle.time_enter_acc_ = millis();
      // TODO: Display safety error message.
    }
  }

  // If engine is not running.
  else
  {
    if (button_power.GetState())
    {
      if (!motorcycle.GetStateSafety())
      {
        if(!engine.Start())
        {
          motorcycle.time_enter_acc_ = millis();
          // TODO: Display error message.
        }
      } else
      {
        // TODO: Display safety error message.
      }
    }

    // If in accessory mode for longer than the auto-off period.
    if (helper::IntervalPassed(motorcycle.time_enter_acc_, kTimeAutoOff)) {
      motorcycle.PowerOff();
    }
  }


  // Regardless of running state
  motorcycle.AutoBrakeLight();
  motorcycle.EmergencyBrakeStrobe();

  // Check and Action Buttons
  // Brake
  button_brake.RefreshState();

  // Horn
  button_horn.RefreshState();

  // Indicator Left
  button_indicator_left.RefreshState();

  // Indicator Right
  button_indicator_right.RefreshState();

  // High Beam
  button_highbeam.RefreshState();
}
