#pragma once
#include <raylib.h>

class Alien {
public:
  Alien(int type, Vector2 position);
  int type;
  Vector2 position;

  static Texture2D alienImages[3];
  static void UnloadImage();

  void Update(int direction);
  void Draw();
  int GetType();
};
