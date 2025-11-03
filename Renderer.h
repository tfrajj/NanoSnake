#ifndef RENDERER_H
#define RENDERER_H

#include <Arduino.h>
#include "config.h"

struct Point {
  uint8_t x;
  uint8_t y;
};

class Renderer {
public:
  static void begin();
  static void drawCell(const Point &p, uint16_t color);
  static void clearCell(const Point &p);
  static void drawSplash();
  static void drawGameOver();
};

#endif // RENDERER_H
