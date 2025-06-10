#pragma once
#include "spaceship.hpp"
#include <raylib.h>
class Game {
public:
  Game();
  ~Game();

  void Update();
  void Draw();
  void HandleInput();

private:
  void DeleteInactiveBullet();
  Spaceship spaceship;
};
