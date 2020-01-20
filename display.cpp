#include "display.h"
#define I2C_ADDRESS 0x3C

Display::Display(void)
{
}

void Display::Setup (void)
{
  Wire.begin();
  Wire.setClock(400000L);
  begin(&Adafruit128x64, I2C_ADDRESS);
  clear();
}

void Display::PrintLine(Display::Symbol const symbol, String const text, Display::Alignment const position_vertical, Display::Alignment const position_horizontal)
{
  // TODO: Clear display - work out how this should be implemented. Should clearing be explicit or automatic and should everything be cleared?
  switch (position_vertical)
  {
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

  switch (position_horizontal)
  {
  case LEFT:
    break;

  case CENTER:
    break;

  case RIGHT:
    break;
  }

  switch (symbol)
  {
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