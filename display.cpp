#include "display.h"
#define I2C_ADDRESS 0x3C

Display::Display(void)
{
}

void Display::Setup(void)
{
  Wire.begin();
  Wire.setClock(400000L);
  begin(&Adafruit128x64, I2C_ADDRESS);
  clear();
}

void Display::PrintLine(Display::Symbol symbol, String text, Display::Alignment position_vertical, Display::Alignment position_horizontal)
{
  // int default_spacing = letterSpacing();
  // setRow(1);
  // setLetterSpacing(0);
  // println("---------------------------------------------------------------");
  // setRow(0);
  // setLetterSpacing(default_spacing);
}

// void Display::PrintLnCenter(char const *string, int row)
// {
//   setRow(row);
//   setCol((displayWidth() - strWidth(string)) / 2);
//   println(string);
//   setCol(0);
//   setRow(0);
// }
