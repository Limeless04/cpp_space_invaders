#pragma once
#include <raylib.h>

class Bullet {
public:
  Bullet(Vector2 position, int speed);
  void Update();
  void Draw();
  bool isActive;
  Rectangle getRect();

private:
  Vector2 position;
  int speed;
};
