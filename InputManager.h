#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <Arduino.h>

class InputManager {
public:
  enum Dir { DIR_NONE, DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT };
  static void begin();
  // Повертає напрямок, якщо натиснута кнопка; інакше DIR_NONE.
  // Простий дебаунс і блокування зворотного ходу робиться в GameCore.
  static Dir readDirection();
  static bool anyButtonPressed();
  static bool isPause();
};

#endif // INPUT_MANAGER_H

