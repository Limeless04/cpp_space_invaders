#include "bullet.hpp"
#include "game.hpp"
#include <raylib.h>
int main() {
  Color GREY = {29, 29, 27, 255};
  int windowWidth = 750;
  int windowHeight = 700;

  InitWindow(windowWidth, windowHeight, "Space Invader");
  SetTargetFPS(60);

  Game game;

  while (!WindowShouldClose()) {
    game.HandleInput();
    BeginDrawing();
    ClearBackground(GREY);

    game.Update();
    game.Draw();

    EndDrawing();
  }

  CloseWindow();
}
