#include "game.hpp"
#include "alien.hpp"
#include "bullet.hpp"
#include "obstacle.hpp"
#include <fstream>
#include <iostream>
#include <raylib.h>
#include <vector>
Game::Game() {
  music = LoadMusicStream("assets/audio/music.ogg");
  explosionSound = LoadSound("assets/audio/explosion.ogg");
  PlayMusicStream(music);
  InitGame();
}

Game::~Game() {
  UnloadMusicStream(music);
  UnloadSound(explosionSound);
  Alien::UnloadImage();
}

void Game::Update() {
  if (run) {

    double currentTime = GetTime();

    if (currentTime - mysteryshipTimeLastSpawned > mysterySpawnInterval) {
      mysteryship.Spawn();
      mysteryshipTimeLastSpawned = GetTime();
      mysterySpawnInterval = GetRandomValue(10, 20);
    }

    for (auto &bullet : spaceship.bullets) {
      bullet.Update();
    }

    MoveAlien();

    AlienShoot();
    for (auto &bullet : alienBullets) {
      bullet.Update();
    }
    DeleteInactiveBullet();
    mysteryship.Update();
    CheckCollision();

    checkAndAdvanceLevel();
  } else {
    if (IsKeyDown(KEY_ENTER)) {
      Reset();
      InitGame();
    }
  }
}

void Game::InitGame() {
  obstacles = CreateObstacle();
  aliens = CreateAliens();
  alienDirection = 1;
  lives = 3;
  run = true;
  score = 0;
  highscore = loadHighScore();
  levels = 1;
  timeLastAlienFired = 0;
  mysterySpawnInterval = 0.0;
  mysteryshipTimeLastSpawned = GetRandomValue(10, 20);
}

void Game::checkHighScore() {
  if (score > highscore) {
    highscore = score;
    saveHighScore(highscore);
  }
}

void Game::checkAndAdvanceLevel() {
  if (aliens.empty()) {
    levels += 1;
    GameOver();
  }
}

void Game::saveHighScore(int highscore) {
  std::ofstream highscoreFile("highscore.txt");
  if (highscoreFile.is_open()) {
    highscoreFile << highscore;
    highscoreFile.close();
  } else {
    std::cerr << "Failed to save highscore to file" << std::endl;
  }
}

int Game::loadHighScore() {
  int loadedHighscore = 0;
  std::ifstream highscoreFile("highscore.txt");
  if (highscoreFile.is_open()) {
    highscoreFile >> loadedHighscore;
    highscoreFile.close();
  } else {
    std::cerr << "Failed to load highscore from file" << std::endl;
  }
  return loadedHighscore;
}

void Game::Reset() {
  spaceship.Reset();
  aliens.clear();
  alienBullets.clear();
  obstacles.clear();
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

  mysteryship.Draw();
}

void Game::HandleInput() {
  if (run) {
    if (IsKeyDown(KEY_LEFT)) {
      spaceship.Move("LEFT");
    } else if (IsKeyDown(KEY_RIGHT)) {
      spaceship.Move("RIGHT");
    } else if (IsKeyPressed(KEY_SPACE)) {
      spaceship.Shoot();
    }
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
    obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 200)}));
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
        GetScreenWidth() - 25) {
      alienDirection = -1;
      MoveDownAlien(4);
    }
    if (alien.position.x < 25) {
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

void Game::CheckCollision() {
  // spaceshiop bullet
  for (auto &bullet : spaceship.bullets) {
    auto it = aliens.begin();
    while (it != aliens.end()) {
      if (CheckCollisionRecs(it->getRect(), bullet.getRect())) {
        PlaySound(explosionSound);
        if (it->type == 1) {
          score += 100;
        } else if (it->type == 2) {
          score += 200;
        } else if (it->type == 3) {
          score += 300;
        }

        checkHighScore();
        it = aliens.erase(it);
        bullet.isActive = false;
      } else {
        ++it;
      }
    }

    for (auto &obstacle : obstacles) {
      auto it = obstacle.blocks.begin();
      while (it != obstacle.blocks.end()) {
        if (CheckCollisionRecs(it->getRect(), bullet.getRect())) {
          it = obstacle.blocks.erase(it);
          bullet.isActive = false;
        } else {
          ++it;
        }
      }
    }

    if (CheckCollisionRecs(mysteryship.getRect(), bullet.getRect())) {
      mysteryship.alive = false;
      bullet.isActive = false;
      score += 500;
      checkHighScore();
      PlaySound(explosionSound);
    }
  }

  // Alien bullet
  for (auto &bullet : alienBullets) {
    if (CheckCollisionRecs(bullet.getRect(), spaceship.getRect())) {
      bullet.isActive = false;
      lives--;
      if (lives == 0) {
        GameOver();
      }
    }
  }
  // ALien collisioni with obstacle
  for (auto &alien : aliens) {
    for (auto &obstacle : obstacles) {
      auto it = obstacle.blocks.begin();
      while (it != obstacle.blocks.end()) {
        if (CheckCollisionRecs(it->getRect(), alien.getRect())) {
          it = obstacle.blocks.erase(it);
        } else {
          it++;
        }
      }
    }
    if (CheckCollisionRecs(alien.getRect(), spaceship.getRect())) {
      GameOver();
    }
  }

  // add alien bullet collide wth obstacle
}

void Game::GameOver() { run = false; }
