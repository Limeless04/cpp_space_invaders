#include "bullet.hpp"
#include <iostream>
#include <raylib.h>
Bullet::Bullet(Vector2 position, int speed) {
  this->position = position;
  this->speed = speed;
  isActive = true;
};

void Bullet::Draw() {
  if (isActive) {
    DrawRectangle(position.x, position.y, 4, 15, {243, 216, 63, 255});
  }
}

void Bullet::Update() {
  position.y += speed;
  if (isActive) {
    if (position.y > GetScreenHeight() || position.y < 0) {
      isActive = false;
    }
  }
}
