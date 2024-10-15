#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "GameManager.h"
#include "BasicEnemy.h"

class EnemyManager {
   public:
    EnemyManager(GameManager* Pgame);
    ~EnemyManager();

    void spawnEnemies();

   private:
    GameManager* game;
    float spawnCooldown;
    sf::Clock clock;
    std::vector<float> lanePositions;
    void setLaneNum(int number);
};

#endif
