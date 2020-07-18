// display.cpp
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#include "display.h"

#include <Arduino.h>
#include <Wire.h>

#include "SSD1306Ascii.h"

#include "utility.h"

Display::Display(byte const i2c_address, DevType display_type)
: kI2C_Address(i2c_address)
, kDisplayType(display_type) {
  Wire.begin();
  Wire.setClock(400000L);
  begin(&display_type, kI2C_Address);
  clear();
}


void Display::PrintLine(Display::Symbol const symbol, String const text, Display::Alignment const position_vertical, Display::Alignment const position_horizontal) {
  // TODO: Clear display - work out how this should be implemented. Should clearing be explicit or automatic and should everything be cleared?
  switch (position_vertical) {
  case TOP:
    setRow(0);
    break;

  case CENTER:
    setRow(1);
    break;

  case BOTTOM:
    setRow(2);
    break;
  }

  switch (position_horizontal) {
  case LEFT:
    break;

  case CENTER:
    break;

  case RIGHT:
    break;
  }

  switch (symbol) {
  case WARNING:
    break;

  case ERROR:
    break;

  case SUCCESS:
    break;

  case NONE:
    break;
  }
}

void Lock(void) {

}

void Unlock(void) {
  
}