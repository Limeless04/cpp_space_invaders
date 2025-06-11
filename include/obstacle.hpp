#pragma once
#include "block.hpp"
#include <raylib.h>
#include <vector>

class Obstacle {
public:
  Obstacle(Vector2 pos);
  void Draw();
  Vector2 pos;
  std::vector<Block> blocks;
  static std::vector<std::vector<int>> grid;
};
