#include "DisplayManager.h"
#include <SPI.h>

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void DisplayManager::begin() {
  tft.initR(INITR_BLACKTAB); // стандартна 160x128/160x120 ініціалізація
  tft.setRotation(0); // орієнтація — підлаштуй при потребі
  tft.fillScreen(COLOR_BG);
}

void DisplayManager::clear() {
  tft.fillScreen(COLOR_BG);
}

void DisplayManager::drawTextCenter(const char* text, uint8_t size) {
  tft.setTextWrap(false);
  tft.setTextSize(size);
  tft.setTextColor(COLOR_TEXT);
  int16_t x1, y1;
  uint16_t w, h;
  tft.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  int16_t x = (DISPLAY_WIDTH - w) / 2;
  int16_t y = (DISPLAY_HEIGHT - h) / 2;
  tft.setCursor(x, y);
  tft.print(text);
}

void DisplayManager::fillRectPx(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  tft.fillRect(x, y, w, h, color);
}

void DisplayManager::fillScreen(uint16_t color) {
  tft.fillScreen(color);
}

