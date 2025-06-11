#include "game.hpp"
#include "obstacle.hpp"
#include <raylib.h>
#include <vector>

Game::Game() { obstacles = CreateObstacle(); }

Game::~Game() {}

void Game::Update() {
  for (auto &bullet : spaceship.bullets) {
    bullet.Update();
  }
  DeleteInactiveBullet();
}
void Game::Draw() {
  spaceship.Draw();
  for (auto &bullet : spaceship.bullets) {
    bullet.Draw();
  }

  for (auto &obstacle : obstacles) {
    obstacle.Draw();
  }
}

void Game::HandleInput() {
  if (IsKeyDown(KEY_LEFT)) {
    spaceship.Move("LEFT");
  } else if (IsKeyDown(KEY_RIGHT)) {
    spaceship.Move("RIGHT");
  } else if (IsKeyPressed(KEY_SPACE)) {
    spaceship.Shoot();
  }
}

void Game::DeleteInactiveBullet() {
  for (auto it = spaceship.bullets.begin(); it != spaceship.bullets.end();) {
    if (!it->isActive) {
      it = spaceship.bullets.erase(it);
    } else {
      ++it;
    }
  }
}

std::vector<Obstacle> Game::CreateObstacle() {
  int obstacleWidth = Obstacle::grid[0].size() * 3;
  float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;
  for (int i = 0; i < 4; i++) {
    float offsetX = (i + 1) * gap + i * obstacleWidth;
    obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 100)}));
  }

  return obstacles;
}
