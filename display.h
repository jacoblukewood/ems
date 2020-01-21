#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include "helper.h"

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

// Define proper RST_PIN if required.
#define RST_PIN -1

class Display : public SSD1306AsciiWire
{
public:
    Display(void);
    enum Symbol
    {
        WARNING,
        ERROR,
        SUCCESS,
        NONE
    };

    enum Alignment
    {
        TOP,
        BOTTOM,
        LEFT,
        RIGHT,
        CENTER
    };
    void Setup(void);
    void PrintLine(Display::Symbol const symbol, String const text, Display::Alignment const position_vertical, Display::Alignment const position_horizontal);
    bool GetLock(void) const;
    void SetLock(bool state);

private:
    bool lock_;
};

#endif // DISPLAY_H
