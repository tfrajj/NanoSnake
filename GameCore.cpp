#include "HardwareSerial.h"
#include "GameCore.h"
#include "DisplayManager.h"
#include "Renderer.h"
#include "InputManager.h"
#include "config.h"

static GameState state = GameState::STATE_MENU;
static Point snake[MAX_SNAKE_LENGTH];
static uint16_t snakeLength = 0;
static Point food;
static InputManager::Dir currentDir = InputManager::DIR_RIGHT;
static InputManager::Dir nextDir = InputManager::DIR_RIGHT;
static InputManager::Dir tmpDir = InputManager::DIR_RIGHT;
static unsigned long lastStepMs = 0;
static uint16_t score = 0;
static bool isPause = false;
static bool toCheckPause = true;

void GameCore::begin() {
  // посів випадковості
  randomSeed(analogRead(A0));
}

GameState GameCore::getState() {
  return state;
}

uint16_t GameCore::getScore() {
  return score;
}

void GameCore::startNewGame() {
  // Очистка дисплея
  DisplayManager::clear();

  // Ініціалізація змійки по центру
  uint8_t startX = FIELD_WIDTH / 2;
  uint8_t startY = FIELD_HEIGHT / 2;

  snakeLength = 3;
  for (uint16_t i = 0; i < snakeLength; ++i) {
    snake[i].x = startX - i; // горизонтально вправо
    snake[i].y = startY;
  }
  currentDir = InputManager::DIR_RIGHT;
  nextDir = InputManager::DIR_RIGHT;
  tmpDir = InputManager::DIR_RIGHT;
  score = 0;

  // Малюємо початкову змійку
  for (uint16_t i = 0; i < snakeLength; ++i) {
    Renderer::drawCell(snake[i], COLOR_CELL);
  }

  // Створюємо першу їжу
  placeFood();
  Renderer::drawCell(food, COLOR_FOOD);

  lastStepMs = millis();
  state = GameState::STATE_PLAYING;
}

static bool GameCore::pointEquals(const Point &a, const Point &b) {
  return a.x == b.x && a.y == b.y;
}

bool GameCore::isCollision(const Point &p) {
  // межі
  if (p.x >= FIELD_WIDTH || p.y >= FIELD_HEIGHT) return true;

  // зіткнення з тілом (перевірка від 0 до snakeLength-1)
  for (uint16_t i = 0; i < snakeLength; ++i) {
    if (pointEquals(snake[i], p)) return true;
  }
  return false;
}

void GameCore::placeFood() {
  // Прості випадкові координати з перевіркою чи не зайнято
  // Якщо поле заповнене — гра завершена (але цього майже не станеться)
  if (snakeLength >= MAX_SNAKE_LENGTH) {
    // немає місця — game over
    state = GameState::STATE_GAMEOVER;
    return;
  }

  Point p;
  bool ok = false;
  uint16_t tries = 0;
  do {
    p.x = random(0, FIELD_WIDTH);
    p.y = random(0, FIELD_HEIGHT);
    ok = true;
    for (uint16_t i = 0; i < snakeLength; ++i) {
      if (pointEquals(snake[i], p)) {
        ok = false;
        break;
      }
    }
    tries++;
    // на випадок чогось — після великої кількості спроб просто лінейно знайдемо вільну клітинку
    if (tries > 500) {
      for (uint8_t yy = 0; yy < FIELD_HEIGHT; ++yy) {
        for (uint8_t xx = 0; xx < FIELD_WIDTH; ++xx) {
          Point q = {xx, yy};
          bool found = false;
          for (uint16_t i = 0; i < snakeLength; ++i) if (pointEquals(snake[i], q)) { found = true; break; }
          if (!found) { p = q; ok = true; goto placed; }
        }
      }
    }
  } while (!ok);
placed:
  food = p;
}

void GameCore::step() {
  // Обробка введення (nextDir встановлюється тут)
  InputManager::Dir d = tmpDir;
  if (d != InputManager::DIR_NONE) {
    // Забороняємо миттєвий поворот на 180 градусів
    if (!((currentDir == InputManager::DIR_UP && d == InputManager::DIR_DOWN) ||
          (currentDir == InputManager::DIR_DOWN && d == InputManager::DIR_UP) ||
          (currentDir == InputManager::DIR_LEFT && d == InputManager::DIR_RIGHT) ||
          (currentDir == InputManager::DIR_RIGHT && d == InputManager::DIR_LEFT))) {
      nextDir = d;
    }
  }

  // Визначаємо наступну голову
  Point newHead = snake[0];
  currentDir = nextDir;
  switch (currentDir) {
    case InputManager::DIR_UP:    if (newHead.y == 0) newHead.y = FIELD_HEIGHT; newHead.y--; break;
    case InputManager::DIR_DOWN:  newHead.y = (newHead.y + 1) % FIELD_HEIGHT; break;
    case InputManager::DIR_LEFT:  if (newHead.x == 0) newHead.x = FIELD_WIDTH; newHead.x--; break;
    case InputManager::DIR_RIGHT: newHead.x = (newHead.x + 1) % FIELD_WIDTH; break;
    default: break;
  }

  // Перевірка зіткнення із самим собою
  for (uint16_t i = 0; i < snakeLength; ++i) {
    if (pointEquals(snake[i], newHead)) {
      state = GameState::STATE_GAMEOVER;
      return;
    }
  }

  // Рух — зсуваємо масив вправо (місце для нової голови)
  // Затираємо хвіст (останній елемент)
  Point oldTail = snake[snakeLength - 1];
  Renderer::clearCell(oldTail);

  for (int i = snakeLength - 1; i > 0; --i) {
    snake[i] = snake[i - 1];
  }
  snake[0] = newHead;

  // Малюємо нову голову
  Renderer::drawCell(snake[0], COLOR_CELL);

  // Якщо з'їли їжу
  if (pointEquals(snake[0], food)) {
    // збільшити довжину: додаємо копію хвоста в кінець
    if (snakeLength < MAX_SNAKE_LENGTH) {
      snake[snakeLength] = oldTail; // старий хвіст лишається
      ++snakeLength;
    }
    score++;
    // помалюємо їжу (буде перерендериться)
    placeFood();
    Renderer::drawCell(food, COLOR_FOOD);
  } else {
    // інакше хвіст уже був очищений — все в порядку
  }
}

void GameCore::update() {
  if (state == GameState::STATE_MENU) {
    // на меню: показати заставку, чекати натискання
    // Renderer::drawSplash();
    if (InputManager::anyButtonPressed()) {
      startNewGame();
    }
    return;
  }

  if (state == GameState::STATE_PLAYING) {
    // Process pause button. >>
    bool pausePressed = InputManager::isPause();

    if (toCheckPause && pausePressed) {
      isPause = !isPause;
      toCheckPause = false;
    }

    if (!pausePressed) { toCheckPause = true; }
    if (isPause) { return; }
    // << Process pause button.

    InputManager::Dir d = InputManager::readDirection();
    if (d != InputManager::DIR_NONE) {
      tmpDir = d;
    }

    unsigned long now = millis();
    if (now - lastStepMs >= GAME_SPEED_DELAY) {
      lastStepMs = now;
      step();
    }
    return;
  }

  if (state == GameState::STATE_GAMEOVER) {
    Renderer::drawGameOver();
    // Чекати будь-якого натискання для рестарту
    if (InputManager::anyButtonPressed()) {
      startNewGame();
    }
    delay(250);
    return;
  }
}
