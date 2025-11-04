#include "Renderer.h"
#include "DisplayManager.h"

void Renderer::begin() {
  // нічого додаткового зараз
}

static inline int16_t cellToPxX(uint8_t cx) {
  return cx * CELL_SIZE;
}
static inline int16_t cellToPxY(uint8_t cy) {
  return cy * CELL_SIZE;
}

void Renderer::drawCell(const Point &p, uint16_t color) {
  int16_t x = cellToPxX(p.x);
  int16_t y = cellToPxY(p.y);
  DisplayManager::fillRectPx(x, y, CELL_SIZE, CELL_SIZE, color);
}

void Renderer::clearCell(const Point &p) {
  drawCell(p, COLOR_BG);
}

void Renderer::drawSplash() {
  tft.fillScreen(COLOR_BG);

  // Назва гри
  tft.setTextColor(COLOR_CELL);
  tft.setTextSize(2);
  tft.setCursor(10, 20);
  tft.print("THE SNAKE");

  // Малюємо "змійку" з квадратів
  int startX = 10, startY = 60;
  int size = CELL_SIZE;

  for (int i = 0; i < 6; i++) {
    tft.fillRect(startX + i * (size + 2), startY, size, size, COLOR_CELL);
  }

  // Малюємо "яблуко"
  tft.fillCircle(startX + 8 * (size + 2), startY + size / 2, size / 2, COLOR_FOOD);

  // Підпис знизу
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(1);
  tft.setCursor(20, 110);
  tft.print("Press any button");
  tft.setCursor(30, 130);
  tft.print("to start");
}

void Renderer::drawGameOver() {
  DisplayManager::drawTextCenter("GAME OVER", 2);
}

