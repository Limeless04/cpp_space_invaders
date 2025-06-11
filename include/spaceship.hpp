#pragma once
#include "bullet.hpp"
#include <raylib.h>
#include <string>
#include <vector>

class Spaceship {
public:
  Spaceship();
  ~Spaceship();
  void Update();
  void Draw();
  void Move(std::string direction);
  void Shoot();
  Rectangle getRect();
  void Reset();
  std::vector<Bullet> bullets;

private:
  Texture2D image;
  Vector2 position;
  double lastFireTime;
  Sound bulletSound;
};
