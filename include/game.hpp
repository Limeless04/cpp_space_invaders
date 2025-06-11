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
  bool run;
  int score;
  int highscore;
  int lives;
  int levels;
  Music music;

private:
  void DeleteInactiveBullet();
  std::vector<Obstacle> CreateObstacle();
  std::vector<Alien> CreateAliens();
  void MoveAlien();
  void MoveDownAlien(int distance);
  void AlienShoot();
  void CheckCollision();
  void GameOver();
  void Reset();
  void InitGame();
  void checkHighScore();
  void saveHighScore(int highscore);
  int loadHighScore();
  void checkAndAdvanceLevel();
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
  Sound explosionSound;
};
