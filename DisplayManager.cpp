#include "DisplayManager.h"
#include <SPI.h>

// TFT driver instance. The pin defines `TFT_CS`, `TFT_DC`, `TFT_RST`
// are expected to be provided in `DisplayManager.h` or `config.h`.
// Adafruit_ST7735 expects SPI to be available; some platforms call
// `SPI.begin()` automatically, but calling it explicitly before
// `begin()` can help on some boards.
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Initialize the display hardware and prepare the screen.
void DisplayManager::begin() {
  // Use the library's predefined init sequence for the "black tab"
  // ST7735 modules. This is the common setting for small 160x128
  // / 160x120 displays. If your module uses a different tab color
  // (green, red, etc.) try a different `INITR_*` constant.
  tft.initR(INITR_BLACKTAB);

  // Set display orientation. Values 0..3 rotate the display by
  // 0/90/180/270 degrees — change if image appears sideways.
  tft.setRotation(0);

  // Clear the screen to the configured background color.
  tft.fillScreen(COLOR_BG);
}

// Clear the display (fill with background color).
void DisplayManager::clear() {
  tft.fillScreen(COLOR_BG);
}

// Draw `text` centered both horizontally and vertically.
// - `size` is the integer text scale (Adafruit_GFX text size).
// Steps:
// 1. Turn off auto-wrap so measured bounds match one-line width.
// 2. Set font scale and color.
// 3. Use `getTextBounds` to measure the text pixel width/height.
// 4. Compute center position using `DISPLAY_WIDTH`/`DISPLAY_HEIGHT`.
// 5. Position cursor and print the text.
void DisplayManager::drawTextCenter(const char* text, uint8_t size) {
  tft.setTextWrap(false);
  tft.setTextSize(size);
  tft.setTextColor(COLOR_TEXT);

  // getTextBounds returns the x/y origin of the bounds (x1,y1)
  // and the measured width/height (w,h) of the rendered string.
  int16_t x1, y1;
  uint16_t w, h;
  tft.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);

  // Center the bounding box inside the display area.
  int16_t x = (DISPLAY_WIDTH - w) / 2;
  int16_t y = (DISPLAY_HEIGHT - h) / 2;
  tft.setCursor(x, y);
  tft.print(text);
}

// Draw a filled rectangle in pixel coordinates. Using `fillRoundRect`
// gives slightly rounded corners (radius = 2). If you prefer sharp
// corners, uncomment the `fillRect` line and remove `fillRoundRect`.
void DisplayManager::fillRectPx(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  // Plain rectangle alternative:
  // tft.fillRect(x, y, w, h, color);
  tft.fillRoundRect(x, y, w, h, 2, color);
}

// Convenience wrapper to fill the whole screen with `color`.
// Colors are 16-bit RGB565 (`uint16_t`).
void DisplayManager::fillScreen(uint16_t color) {
  tft.fillScreen(color);
}

