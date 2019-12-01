#include "display.h"
#define I2C_ADDRESS 0x3C

Display::Display(){
    
}

void Display::Setup() {
    Wire.begin();
    Wire.setClock(400000L);
    begin(&Adafruit128x64, I2C_ADDRESS);
    clear();
}

void Display::PrintHLine(int row) {
  int default_spacing = letterSpacing();
  setRow(row);
  setLetterSpacing(0);
  println("---------------------------------------------------------------");
  setRow(0);
  setLetterSpacing(default_spacing);
}

void Display::PrintLnCenter(const char * string, int row) {
  setRow(row);
  setCol((displayWidth() - strWidth(string)) / 2);
  println(string);
  setCol(0);
  setRow(0);
}
