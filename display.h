// display.h
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "SSD1306AsciiWire.h"

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

// Define proper RST_PIN if required.
#define RST_PIN -1

class Display : private SSD1306AsciiWire {
 public:
    enum Symbol {
        WARNING,
        ERROR,
        SUCCESS,
        NONE
    };
    enum Alignment {
        TOP,
        BOTTOM,
        LEFT,
        RIGHT,
        CENTER
    };

    Display(byte const i2c_address, DevType display_type);

    void PrintLine(Display::Symbol const symbol, String const text, Display::Alignment const position_vertical, Display::Alignment const position_horizontal);

    void Lock();

    void Unlock();

 private:
    DevType kDisplayType = Adafruit128x32;
    byte const kI2C_Address = 0x3C;
};

#endif  // DISPLAY_H_
