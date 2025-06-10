#include "game.hpp"
#include <iostream>
#include <raylib.h>
Game::Game() {}

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
