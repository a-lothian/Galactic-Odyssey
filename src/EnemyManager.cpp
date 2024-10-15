#include "EnemyManager.h"
#include "GameManager.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

EnemyManager::EnemyManager(GameManager* Pgame)
    : game(Pgame), spawnCooldown(2.0f) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));  // set random seed

    setLaneNum(3);  // starting number of lanes
}

void EnemyManager::spawnEnemies() {
    sf::Time elapsed = clock.getElapsedTime();
    if (elapsed.asSeconds() >= spawnCooldown) {
        int laneNum = std::rand() % 7 + 1;  // random number of lanes
        setLaneNum(laneNum);
        clock.restart();
        // base spawn cooldown based on difficulty with randomness
        float difficultyFactor = game->difficulty;
        spawnCooldown = std::max(0.5f, 2.0f - difficultyFactor * 0.1f + static_cast<float>(rand()) / RAND_MAX * 0.5f);
        for (int i = 0; i < laneNum; ++i) {
            float spawnX = lanePositions[i];
            float spawnY = 0.0f;

            int baseHealth = 1;
            float baseSpeed = 1.0f;

            int health = baseHealth + static_cast<int>(difficultyFactor * 0.5f) + rand() % 2;
            float speed = baseSpeed + difficultyFactor * 0.1f + static_cast<float>(rand()) / RAND_MAX * 0.5f;
            float weaponCooldown = 1 / difficultyFactor + static_cast<float>(rand()) / RAND_MAX * 0.5f;

            game->createBasicEnemy_Single(spawnX, spawnY, health, speed, weaponCooldown);
        }
    }
}

void EnemyManager::setLaneNum(int laneNum) {
    float laneWidth = static_cast<float>(X_RES) / laneNum;

    lanePositions.resize(laneNum);

    for (int i = 0; i < laneNum; ++i) {
        float x = (i + 0.5f) * laneWidth;
        lanePositions[i] = x;
    }
}
