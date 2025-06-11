#pragma once
#include <raylib.h>

class Alien {
public:
  Alien(int type, Vector2 position);
  Texture2D image;
  int type;
  Vector2 position;

  void Update();
  void Draw();
  int GetType();
};
