#include "game.hpp"
#include "alien.hpp"
#include "bullet.hpp"
#include "obstacle.hpp"
#include <raylib.h>
#include <vector>

Game::Game() {
  obstacles = CreateObstacle();
  aliens = CreateAliens();
  alienDirection = 1;
  timeLastAlienFired = 0;
}

Game::~Game() { Alien::UnloadImage(); }

void Game::Update() {
  for (auto &bullet : spaceship.bullets) {
    bullet.Update();
  }

  MoveAlien();

  AlienShoot();
  for (auto &bullet : alienBullets) {
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

  for (auto &alien : aliens) {
    alien.Draw();
  }

  for (auto &bullet : alienBullets) {
    bullet.Draw();
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

  for (auto it = alienBullets.begin(); it != alienBullets.end();) {
    if (!it->isActive) {
      it = alienBullets.erase(it);
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

std::vector<Alien> Game::CreateAliens() {
  std::vector<Alien> aliens;
  for (int row = 0; row < 5; row++) {
    for (int column = 0; column < 11; column++) {
      int cellSize = 55;
      int offsetX = 75;
      int offsetY = 110;

      int alienType;
      if (row == 0) {
        alienType = 3;
      } else if (row == 1 || row == 2) {
        alienType = 2;
      } else {
        alienType = 1;
      }
      float pos_x = offsetX + column * cellSize;
      float pos_y = offsetY + row * cellSize;
      aliens.push_back(Alien(alienType, {pos_x, pos_y}));
    }
  }
  return aliens;
}

void Game::MoveAlien() {
  for (auto &alien : aliens) {
    if (alien.position.x + alien.alienImages[alien.type - 1].width >
        GetScreenWidth()) {
      alienDirection = -1;
      MoveDownAlien(4);
    }
    if (alien.position.x < 0) {
      alienDirection = 1;
      MoveDownAlien(4);
    }
    alien.Update(alienDirection);
  }
}

void Game::MoveDownAlien(int distance) {
  for (auto &alien : aliens) {
    alien.position.y += distance;
  }
}

void Game::AlienShoot() {
  double currentTime = GetTime();
  if (currentTime - timeLastAlienFired >= alienBulletInterval &&
      !aliens.empty()) {
    int randomIndex = GetRandomValue(0, aliens.size() - 1);
    Alien &alien = aliens[randomIndex];
    alienBullets.push_back(
        Bullet({alien.position.x + alien.alienImages[alien.type - 1].width / 2,
                alien.position.y + alien.alienImages[alien.type - 1].height},
               6));

    timeLastAlienFired = GetTime();
  }
}
