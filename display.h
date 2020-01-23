#ifndef EMS_DISPLAY_SRC_H_
#define EMS_DISPLAY_SRC_H_

#include "SSD1306AsciiWire.h"

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

// Define proper RST_PIN if required.
#define RST_PIN -1

class Display : public SSD1306AsciiWire
{
public:
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

    Display(void);

    bool GetLock(void) const;
    void PrintLine(Display::Symbol const symbol, String const text, Display::Alignment const position_vertical, Display::Alignment const position_horizontal);
    void Setup(void);
    void SetLock(bool state);

private:
    bool lock_;
};

#endif // EMS_DISPLAY_SRC_H_
