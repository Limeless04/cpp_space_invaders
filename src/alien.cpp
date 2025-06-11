#include "alien.hpp"
#include <raylib.h>

Alien::Alien(int type, Vector2 position) {
  this->type = type;
  this->position = position;

  switch (type) {
  case 1:
    image = LoadTexture("assets/graphics/alien_1.png");
    break;
  case 2:
    image = LoadTexture("assets/graphics/alien_2.png");
    break;
  case 3:
    image = LoadTexture("assets/graphics/alien_3.png");
    break;
  }
}

void Alien::Draw() { DrawTextureV(image, position, WHITE); }

int Alien::GetType() { return type; }
