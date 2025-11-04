#ifndef CONFIG_H
#define CONFIG_H

// ------------------------
// Display - ST7735 (SPI)
// Змінити пін підключення CS/DC/RST за потреби.
// ------------------------
#define TFT_CS   10
#define TFT_DC    9
#define TFT_RST   8  // або -1 якщо не підключено до RST

// Фізична роздільність екрана (px)
#define DISPLAY_WIDTH  128
#define DISPLAY_HEIGHT 160

// Розмір клітинки (компіляційний макрос для перерахунку FIELD_WIDTH/HEIGHT)
// Можливі значення: 4 або 8 (або інші які підходять поділу дисплея)
#define CELL_SIZE 8

// Частота оновлення руху змійки (мс, можна змінити)
#define GAME_SPEED_DELAY 250

// Кнопки (по твоїм значенням)
#define PIN_UP    4
#define PIN_DOWN  2
#define PIN_LEFT  3
#define PIN_RIGHT 5

#define PIN_PAUSE 6

// Обчислені значення
#define FIELD_WIDTH  (DISPLAY_WIDTH / CELL_SIZE)
#define FIELD_HEIGHT (DISPLAY_HEIGHT / CELL_SIZE)
#define MAX_SNAKE_LENGTH (FIELD_WIDTH * FIELD_HEIGHT)

// Кольори (16-bit) https://rgbcolorpicker.com/565
#define COLOR_BG    0x0000
#define COLOR_CELL  0x0c88
#define COLOR_FOOD  0xff00
#define COLOR_TEXT  0xd154

#endif // CONFIG_H
