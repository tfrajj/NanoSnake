#ifndef CONFIG_H
#define CONFIG_H

// ------------------------
// Display - ST7735 (SPI)
// Change the CS/DC/RST connection pins if needed.
// ------------------------
#define TFT_CS   10
#define TFT_DC    9
#define TFT_RST   8  // or -1 if not connected to RST

// Physical screen resolution (px)
#define DISPLAY_WIDTH  128
#define DISPLAY_HEIGHT 160

// Cell size (compile-time macro for calculating FIELD_WIDTH/HEIGHT)
// Possible values: 4 or 8 (or others that fit the display division)
#define CELL_SIZE 8

// Snake movement update frequency (ms, can be changed)
#define GAME_SPEED_DELAY 250

// Buttons (according to your values)
#define PIN_UP    4
#define PIN_DOWN  2
#define PIN_LEFT  3
#define PIN_RIGHT 5

#define PIN_PAUSE 6

// Calculated values
#define FIELD_WIDTH  (DISPLAY_WIDTH / CELL_SIZE)
#define FIELD_HEIGHT (DISPLAY_HEIGHT / CELL_SIZE)
#define MAX_SNAKE_LENGTH (FIELD_WIDTH * FIELD_HEIGHT)

// Colors (16-bit) https://rgbcolorpicker.com/565
#define COLOR_BG    0x0000
#define COLOR_CELL  0x0c88
#define COLOR_FOOD  0xff00
#define COLOR_TEXT  0xd154

#endif // CONFIG_H
