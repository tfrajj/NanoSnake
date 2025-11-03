#ifndef GAME_CORE_H
#define GAME_CORE_H

#include "Renderer.h"
#include "InputManager.h"
#include <Arduino.h>

enum GameState { STATE_MENU, STATE_PLAYING, STATE_GAMEOVER };

class GameCore {
public:
  static void begin();
  static void startNewGame();
  static void update(); // має викликатися часто в loop()
  static GameState getState();
  static uint16_t getScore();
private:
  static void step();
  static bool isCollision(const Point &p);
  static void placeFood();
  static bool pointEquals(const Point &a, const Point &b);
};

#endif // GAME_CORE_H

