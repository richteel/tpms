#ifndef DISPLAY_128x160_H
#define DISPLAY_128x160_H

#include "bitmap.h"
#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h>  // Hardware-specific library for ST7735

Adafruit_ST7735 display = Adafruit_ST7735(&LCD_SPI, LCD_CS, LCD_DC, LCD_RESET);


void DisplayInit() {
  SER.printf("\nDisplay Tab is %s\n\n", ST7735TabName[unitSettings.st7735Tab]);
  switch (unitSettings.st7735Tab) {
    case Display_ST7735_Tabs::GreenTab:
      display.initR(INITR_GREENTAB);  // initialize a ST7735S chip, green tab
      break;
    case Display_ST7735_Tabs::RedTab:
      display.initR(INITR_REDTAB);  // initialize a ST7735S chip, red tab
      break;
    case Display_ST7735_Tabs::BlackTab:
      display.initR(INITR_BLACKTAB);  // initialize a ST7735S chip, black tab
      break;
  }
  display.setRotation(3);
  display.fillScreen(ST7735_BLACK);
  display.setTextWrap(false);
}

void DisplayWarning(char* msg, int16_t x, int16_t y) {
  display.setCursor(x, y);
  display.setTextSize(1);
  display.print(msg);
}

void DrawBackground() {
  int LineSplitCol = 72;

  display.drawBitmap(0, 8, car_bmp_128x60_car, 160, 128, ST77XX_WHITE);
  display.drawLine(8, LineSplitCol, 54, LineSplitCol, ST77XX_BLUE);
  display.drawLine(108, LineSplitCol, 154, LineSplitCol, ST77XX_BLUE);
}

void PrintFreq() {
  display.setCursor(118, 0);
  display.print(tpmsFrequencyName[carSettings.freq]);
}

void ShowTemperatureType() {
  display.drawCircle(80, 120, 2, ST77XX_MAGENTA);
  display.setCursor(84, 118);
  display.setTextColor(ST77XX_MAGENTA);
  display.setTextSize(1);
  display.print(temperatureUnitSymbol[unitSettings.temperatureUnit]);
}

void DrawTitle() {
  //background header
  display.fillRect(0, 0, 159, 16, ST77XX_BLUE);

  display.setCursor(2, 0);
  display.setTextColor(ST77XX_YELLOW);
  display.setTextSize(1);
  display.print(tpmsSensorName[carSettings.tpmsSensorType]);
  PrintFreq();
  display.setCursor(45, 8);
  display.setTextColor(ST77XX_YELLOW);
  display.setTextSize(1);
  display.print(F(" JSMSolutions V"));
  display.print(VERSION);

  ShowTemperatureType();
}

void ScreenSetup() {
  DisplayInit();
  DrawBackground();
  DrawTitle();
}


#endif  // DISPLAY_128x160_H