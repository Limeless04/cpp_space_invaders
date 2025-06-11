#include "game.hpp"
#include <raylib.h>
#include <string>

std::string formatWithLeadingZero(int number, int width) {
  std::string numberText = std::to_string(number);
  int leadingZero = width - numberText.length();
  return numberText = std::string(leadingZero, '0') + numberText;
}

int main() {
  Color GREY = {29, 29, 27, 255};
  Color yellow = {243, 216, 63, 255};
  int offset = 50;
  int windowWidth = 750;
  int windowHeight = 700;

  InitWindow(windowWidth + offset, windowHeight + 2 * offset, "Space Invader");
  InitAudioDevice();
  Font font = LoadFontEx("assets/monogram.ttf", 64, 0, 0);
  SetTargetFPS(60);
  Texture2D spaceshipImage = LoadTexture("assets/graphics/spaceship.png");
  Game game;

  while (!WindowShouldClose()) {
    UpdateMusicStream(game.music);
    game.HandleInput();
    BeginDrawing();
    ClearBackground(GREY);
    DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, yellow);
    DrawLineEx({25, 730}, {775, 730}, 3, yellow);
    if (game.run) {
      std::string levelText = "LEVEL " + std::to_string(game.levels);
      DrawTextEx(font, levelText.c_str(), {570, 740}, 34, 2, yellow);

    } else {
      DrawTextEx(font, "PRESS ENTER", {50, 745}, 34, 2, yellow);
      DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, yellow);
    }

    float x = 50.0;
    for (int i = 0; i < game.lives; i++) {
      DrawTextureV(spaceshipImage, {x, 745}, WHITE);
      x += 50;
    }

    DrawTextEx(font, "Score", {50, 15}, 34, 2, yellow);
    std::string scoreText = formatWithLeadingZero(game.score, 5);
    DrawTextEx(font, scoreText.c_str(), {50, 40}, 34, 2, yellow);

    DrawTextEx(font, "Hi-Score", {570, 15}, 34, 2, yellow);
    std::string highscoreText = formatWithLeadingZero(game.highscore, 5);
    DrawTextEx(font, highscoreText.c_str(), {570, 40}, 34, 2, yellow);

    game.Update();
    game.Draw();
    EndDrawing();
  }

  CloseWindow();
  CloseAudioDevice();
}
