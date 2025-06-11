#include "alien.hpp"
#include "game.hpp"
#include <raylib.h>
int main() {
  Color GREY = {29, 29, 27, 255};
  int windowWidth = 750;
  int windowHeight = 700;

  InitWindow(windowWidth, windowHeight, "Space Invader");
  SetTargetFPS(60);

  Game game;
  Alien alien = Alien(1, {100, 100});

  while (!WindowShouldClose()) {
    game.HandleInput();
    BeginDrawing();
    ClearBackground(GREY);

    game.Update();
    game.Draw();
    alien.Draw();
    EndDrawing();
  }

  CloseWindow();
}
