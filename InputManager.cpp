#include "InputManager.h"
#include "config.h"

void InputManager::begin() {
  pinMode(PIN_UP, INPUT_PULLUP);
  pinMode(PIN_DOWN, INPUT_PULLUP);
  pinMode(PIN_LEFT, INPUT_PULLUP);
  pinMode(PIN_RIGHT, INPUT_PULLUP);

  pinMode(PIN_PAUSE, INPUT_PULLUP);
  // Немає складного апаратного дебаунсу — в коді гри достатньо простого фільтра.
}

static bool isPressed(uint8_t pin) {
  return digitalRead(pin) == HIGH; // PULLUP -> LOW коли натиснуто
}

InputManager::Dir InputManager::readDirection() {
  if (isPressed(PIN_UP))    return DIR_UP;
  if (isPressed(PIN_DOWN))  return DIR_DOWN;
  if (isPressed(PIN_LEFT))  return DIR_LEFT;
  if (isPressed(PIN_RIGHT)) return DIR_RIGHT;
  return DIR_NONE;
}

bool InputManager::isPause() {
  return isPressed(PIN_PAUSE);
}

bool InputManager::anyButtonPressed() {
  return isPressed(PIN_UP) || isPressed(PIN_DOWN) || isPressed(PIN_LEFT) || isPressed(PIN_RIGHT);
}
