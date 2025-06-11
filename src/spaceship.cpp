#include "spaceship.hpp"
#include <iostream>
#include <raylib.h>
#include <string>

Spaceship::Spaceship() {
  image = LoadTexture("assets/graphics/spaceship.png");
  position.x = (GetScreenWidth() - image.width) / 2;
  position.y = GetScreenHeight() - image.height - 100;
  lastFireTime = 0;
  bulletSound = LoadSound("assets/audio/laser.ogg");
};

Spaceship::~Spaceship() {
  UnloadTexture(image);
  UnloadSound(bulletSound);
}

void Spaceship::Draw() { DrawTextureV(image, position, WHITE); }

void Spaceship::Move(std::string direction) {
  if (direction == "LEFT") {
    position.x -= 7;
    if (position.x < 25) {
      position.x = 25;
    }
  } else if (direction == "RIGHT") {
    position.x += 7;
    if (position.x > GetScreenWidth() - image.width - 25) {
      position.x = GetScreenWidth() - image.width - 25;
    }
  }
}

void Spaceship::Shoot() {

  if (GetTime() - lastFireTime >= 0.35) {

    bullets.push_back(
        Bullet({position.x + image.width / 2 - 2, position.y}, -6));
    lastFireTime = GetTime();
    PlaySound(bulletSound);
  }
}

Rectangle Spaceship::getRect() {
  return {position.x, position.y, float(image.width), float(image.height)};
}

void Spaceship::Reset() {
  position.x = (GetScreenWidth() - image.width) / 2.0f;
  position.y = GetScreenHeight() - image.height - 100;
  bullets.clear();
}
