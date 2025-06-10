#include "spaceship.hpp"
#include <iostream>
#include <raylib.h>
#include <string>

Spaceship::Spaceship() {
  image = LoadTexture("assets/graphics/spaceship.png");
  position.x = (GetScreenWidth() - image.width) / 2;
  position.y = GetScreenHeight() - image.height;
  lastFireTime = 0;
};

Spaceship::~Spaceship() { UnloadTexture(image); }

void Spaceship::Draw() { DrawTextureV(image, position, WHITE); }

void Spaceship::Move(std::string direction) {
  if (direction == "LEFT") {
    position.x -= 7;
    if (position.x < 0) {
      position.x = 0;
    }
  } else if (direction == "RIGHT") {
    position.x += 7;
    if (position.x > GetScreenWidth() - image.width) {
      position.x = GetScreenWidth() - image.width;
    }
  }
}

void Spaceship::Shoot() {

  if (GetTime() - lastFireTime >= 0.35) {

    bullets.push_back(
        Bullet({position.x + image.width / 2 - 2, position.y}, -6));
    lastFireTime = GetTime();
  }
}
