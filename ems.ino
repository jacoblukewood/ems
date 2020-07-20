// ems.ino
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#include <Arduino.h>

#include "motorcycle.h"
#include "utility.h"

Motorcycle motorcycle;

void setup() {
  // Wait for valid key. The reed switch will keep the power on for this time, turning off if a key is removed.
  while (!motorcycle.rfid_reader_.IsValidKeyPresent()) {  // While loop will block code from proceeding until key is found.
    motorcycle.display_dash_.PrintLine(Display::Symbol::ERROR, "Invalid Key", Display::Alignment::CENTER, Display::Alignment::CENTER);
  }

  // Permanently Power on EMU. Output mode.
  motorcycle.PowerOn();
}

void loop() {
  if (motorcycle.engine_.IsRunning()) {
    if (motorcycle.engine_.IsRedlining()) {
      motorcycle.display_dash_.PrintLine(Display::Symbol::WARNING, "RPM Limit Exceeded", Display::Alignment::CENTER, Display::Alignment::CENTER);
      motorcycle.display_dash_.Lock();
    } else {
      motorcycle.display_dash_.Unlock();
    }

    // Display odometer.
    motorcycle.display_dash_.PrintLine(Display::Symbol::NONE, String(motorcycle.odometer_.GetOdometer()), Display::Alignment::CENTER, Display::Alignment::CENTER);

    if (!motorcycle.IsSafeToRide()) {
      motorcycle.display_dash_.PrintLine(Display::Symbol::WARNING, "Stand Engaged", Display::Alignment::CENTER, Display::Alignment::CENTER);
      motorcycle.engine_.Stop();
      motorcycle.SetTimeOutputModeStarted(millis());
    }
  } else {
    const char* auto_off_message;
    const int time_until_auto_off = (motorcycle.GetTimeOutputModeStarted() + motorcycle.GetOutputModeTimeout()) - millis();
    sprintf("Ready to Start - Auto Off in %i", auto_off_message, time_until_auto_off);

    motorcycle.display_dash_.PrintLine(Display::Symbol::SUCCESS, auto_off_message, Display::Alignment::CENTER, Display::Alignment::CENTER);

    if (utility::IntervalPassed(motorcycle.GetTimeOutputModeStarted(), motorcycle.GetOutputModeTimeout())) {
      motorcycle.PowerOff();
    }
  }

  // Regardless of running state
  if(motorcycle.IsSlowingDownOrStopped()) {
    if(motorcycle.IsBrakingRapidly()) {
      if(motorcycle.light_tail_.timeLastChanged_ + ((60 / motorcycle.GetEmergencyStrobeCyclesPerSecond()) * 1000) < millis()) {
        if(motorcycle.light_tail_.IsOn()) {
          motorcycle.light_tail_.Off();
        } else {
          motorcycle.light_tail_.On();
        }

        motorcycle.light_tail_.timeLastChanged_ = millis();
      }
    } else {
      motorcycle.light_tail_.On();
    }
      motorcycle.light_tail_.Lock();
  } else {
    motorcycle.light_tail_.Unlock();
  }

  motorcycle.RefreshButtons();
}