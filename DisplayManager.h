#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "config.h"

class DisplayManager {
public:
  static void begin();
  static void clear();
  static void drawTextCenter(const char* text, uint8_t size = 1);
  static void fillRectPx(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
  static void fillScreen(uint16_t color);
};

extern Adafruit_ST7735 tft;

#endif // DISPLAY_MANAGER_H
