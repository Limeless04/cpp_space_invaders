#pragma once
#include "obstacle.hpp"
#include "spaceship.hpp"
#include <raylib.h>
#include <vector>
class Game {
public:
  Game();
  ~Game();

  void Update();
  void Draw();
  void HandleInput();

private:
  void DeleteInactiveBullet();
  std::vector<Obstacle> CreateObstacle();
  Spaceship spaceship;
  std::vector<Obstacle> obstacles;
};
