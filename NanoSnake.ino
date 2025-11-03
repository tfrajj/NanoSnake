#include "config.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "Renderer.h"
#include "GameCore.h"

void setup() {
  Serial.begin(115200);
  DisplayManager::begin();
  InputManager::begin();
  Renderer::begin();
  GameCore::begin();

  // Показати splash
  Renderer::drawSplash();
  delay(800);
}

void loop() {
  GameCore::update();
  // Немає додаткових дій в loop — все в GameCore
}
