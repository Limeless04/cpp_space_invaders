#pragma once
#include "alien.hpp"
#include "mysteryship.hpp"
#include "obstacle.hpp"
#include "spaceship.hpp"
#include <raylib.h>
#include <vector>
class Game {
public:
  Game();
  ~Game();

  void Update();
  void Draw();
  void HandleInput();

private:
  void DeleteInactiveBullet();
  std::vector<Obstacle> CreateObstacle();
  std::vector<Alien> CreateAliens();
  void MoveAlien();
  void MoveDownAlien(int distance);
  void AlienShoot();
  Spaceship spaceship;
  std::vector<Obstacle> obstacles;
  std::vector<Alien> aliens;
  int alienDirection;
  std::vector<Bullet> alienBullets;
  constexpr static float alienBulletInterval = 0.35;
  float timeLastAlienFired;
  MysteryShip mysteryship;
  float mysterySpawnInterval;
  float mysteryshipTimeLastSpawned;
};
