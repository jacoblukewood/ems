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
#include "sensor.h"
#include "helper.h"
#include "button.h"
#include "rfid.h"

// Constants
// Configurable
static float const kTachometerRunningMinimum = 700.0;     // RPM value at which the engine is determined to have started.
static float const kAutoOffIndicatorOffMinSpeed = 25.0;   // Speed that the bike must be above for > kAutoOffIndicatorOffTimeout for the indicators to be turned off automatically.
static float const kAutoOffIndicatorOffTimeout = 10.0;    // Time in seconds the indicators must be left on while the bike is travling above kAutoOffIndicatorOffMinSpeed to be automatically turned off.
static float const kAutoBrakeDecelerationRate = 0.04;     // Decelleration rate in m/s2 that auto brake is activated at/above.
static float const kEmergencyBrakeDecelerationRate = 6.0; // Deceleration rate in m/s2 that the emergency brake lights are activated at/above. (5.2.23.1. The signal shall not be activated when the vehicle deceleration is below 6 m/s² but it may be generated at any deceleration at or above this value, the actual value being defined by the vehicle manufacturer. - Vehicle Standard (Australian Design Rule 31/04 – Brake Systems for Passenger Cars) 2017).
static unsigned int const kTimeoutCranking = 2000;        // Timeout in milliseconds for auto start.
static unsigned int const kOffHoldTime = 5000;            // Time in milliseconds to hold the power button to trigger it.
static unsigned int const kFlashRate = 120;               // Times per minute to flash indicators. (6.3.11.1.1. the light flashing frequency shall be 90 ± 30 times per minute; - Vehicle Standard (Australian Design Rule 19/00 – Installation of Lighting and Light-Signalling Devices on L-Group Vehicles) 2006).
static unsigned int const kBrightnessTailLight = 20;      // Tail light (when not activated as a brake light) brightness. Value between 0 (off) - 255 (high, avoid as this is the break light brightness).
static unsigned int const kBrightnessBrakeLight = 255;
static unsigned int const kBrightnessHeadlight = 200;
static unsigned int const kBrightnessHighbeam = 255;
static unsigned int const kTachometerRedline = 8000;      // RPM value at which the motorcycle meets redline.
static unsigned int const kTailLightStrobeInterval = 100; // Time in milliseconds between on/off strobe.
static unsigned int const kTimeAutoOff = 10000;           // Timeeout in milliseconds to leave accessory mode and power off.
static byte const kRFIDKeyList[][4] = {                   // List of RFID key UIDs in hex.
    {0xF9, 0xAC, 0x41, 0xC2},
    {0xF9, 0xAC, 0x41, 0xC2}};

// Non-Configurable
// static unsigned long const kOdometerStart; // Odometer reading from EEPROM at motorcycle startup. TODO: Fix.

// Variables
static unsigned long OdometerTrip = 0; // Odometer value for the trip, to be added to kOdometerStart and written after > 1 hour and at power down.

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
static unsigned int const kPinInputButtonIndicatorLeft = 2;
static unsigned int const kPinInputButtonIndicatorRight = 3;
static unsigned int const kPinInputButtonPower = 4;
static unsigned int const kPinInputButtonHorn = 5;
static unsigned int const kPinInputButtonHighBeam = 6;
static unsigned int const kPinInputButtonBrake = 7;

// Sensors
// Analog
static unsigned int const kPinInputSensorTachometer = A0;
static unsigned int const kPinInputSensorSpeed = A1;
// Digital
static unsigned int const kPinInputSensorNeutral = 14;
static unsigned int const kPinInputSensorSideStand = 15;

// RFID
static unsigned int const kPinInputPinSS = 53;
static unsigned int const kPinInputRST = 5;

// Objects
// Sensors
Sensor sensor_neutral(kPinInputSensorNeutral);
Sensor sensor_side_stand(kPinInputSensorSideStand);
Sensor sensor_tachometer(kPinInputSensorTachometer); // TODO: Add analog reading to sensor class and then change the tachometer inputs below in the parameters.
Sensor sensor_speed(kPinInputSensorSpeed);

// Outputs
Display display_dash;
Light light_tail(kPinOutputTailLight, kBrightnessTailLight, kBrightnessBrakeLight);                                                                  // TODO: Figure out how to move this down below, but it is needed in the Motorcycle object below. Maybe move these to header file?
Engine engine(kTimeoutCranking, kTachometerRunningMinimum, kTachometerRedline, kPinOutputPoints, kPinOutputStarterMotor, kPinInputSensorTachometer); // TODO: Same with this.
Motorcycle motorcycle(engine, light_tail, kPinInputSensorSpeed, kAutoBrakeDecelerationRate, kEmergencyBrakeDecelerationRate, kTailLightStrobeInterval, display_dash, kPinOutputPower, sensor_side_stand);

// Accessories
Indicator indicator_left(kPinOutputIndicatorLeft, kFlashRate, motorcycle);
Indicator indicator_right(kPinOutputIndicatorRight, kFlashRate, motorcycle);
Accessory horn(kPinOutputHorn);
Light light_headlight(kPinOutputHeadlight, kBrightnessHeadlight, kBrightnessHighbeam);
Button button_indicator_left(kPinInputButtonIndicatorLeft, indicator_left, Button::ButtonTypes::kToggle);
Button button_indicator_right(kPinInputButtonIndicatorRight, indicator_right, Button::ButtonTypes::kToggle);
Button button_horn(kPinInputButtonHorn, horn, Button::ButtonTypes::kMomentary);
Button button_highbeam(kPinInputButtonHighBeam, light_headlight, Button::ButtonTypes::kToggle);
Button button_brake(kPinInputButtonBrake, light_tail, Button::ButtonTypes::kMomentary);
// Button button_power(kPinInputButtonPower, motorcycle, Button::ButtonTypes::kPower);
RFID rfid_seat(kPinInputPinSS, kPinInputRST);

void setup()
{
  display_dash.Setup();

  // Wait for valid key. The reed switch will keep the power on for this time, turning off if a key is removed.
  while (!rfid_seat.Verify(kRFIDKeyList))
  {
    display_dash.PrintLine(Display::Symbol::ERROR, "Invalid Key", Display::Alignment::CENTER, Display::Alignment::CENTER);
  }

  // Permanently Power on EMU. Accessory mode.
  motorcycle.PowerOn();
  display_dash.PrintLine(Display::Symbol::SUCCESS, "Ready", Display::Alignment::CENTER, Display::Alignment::CENTER);
}

void loop()
{
  // If engine is running.
  if (engine.GetState())
  {
    // If power button is pressed.
    //   if (button_power.GetState())
    //   {
    //     engine.Stop();
    //     motorcycle.time_enter_acc_ = millis();
    //   }
    //   // If it is unsafe.
    //   if (motorcycle.GetStateSafety())
    //   {
    //     engine.Stop();
    //     motorcycle.time_enter_acc_ = millis();
    //     display_dash.PrintLine(Display::Symbol::WARNING, "Stand Engaged", Display::Alignment::CENTER, Display::Alignment::CENTER);
    //   }
  }

  // If engine is not running.
  else
  {
    // if (button_power.GetState())
    // {
    //   if (!motorcycle.GetStateSafety())
    //   {
    //     if (!engine.Start())
    //     {
    //       motorcycle.time_enter_acc_ = millis();
    //       display_dash.PrintLine(Display::Symbol::ERROR, "Failed to Start", Display::Alignment::CENTER, Display::Alignment::CENTER);
    //     }
    //   }
    //   else
    //   {
    //     display_dash.PrintLine(Display::Symbol::WARNING, "Stand is Engaged", Display::Alignment::CENTER, Display::Alignment::CENTER);
    //   }
    // }

    // If in accessory mode for longer than the auto-off period.
    if (helper::IntervalPassed(motorcycle.time_enter_acc_, kTimeAutoOff))
    {
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
