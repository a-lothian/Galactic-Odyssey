#include "EnemyManager.h"
#include "GameManager.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

EnemyManager::EnemyManager(GameManager* game)
    : game(game), spawnCooldown(2.0f) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));  // set random seed

    setLaneNum(3);  // starting number of lanes
}

// void EnemyManager::allocateEnemies() {
//     std::vector<int> availableLanes;

//     for (int i = 0; i < 7; ++i) {
//         bool laneOccupied = false;
//         float laneX = lanePositions[i];

//         // Check if any enemy in lane
//         for (BasicEnemy* enemy : game->enemies) {
//             if (std::abs(enemy->pos.x - laneX) < 10.0f && enemy->pos.y < 100.0f) {
//                 laneOccupied = true;
//                 break;
//             }
//         }
//         if (!laneOccupied) {
//             availableLanes.push_back(i);
//         }
//     }

//     if (!availableLanes.empty()) {
//         // choose a random available lane
//         int laneIndex = availableLanes[rand() % availableLanes.size()];
//         float spawnX = lanePositions[laneIndex];
//         float spawnY = -50.0f;  // Spawn above the screen

//         // adjust enemy attributes
//         float difficultyFactor = game->difficulty;

//         // Create and initialize the enemy
//         BasicEnemy* enemy = game->createBasicEnemy_Single(spawnX, spawnY);
//         enemy->health = health;
//         enemy->speed = speed;

//         // Add enemy to the game's enemy list
//         game->enemies.push_back(enemy);
//     }
// }

void EnemyManager::spawnEnemies() {
    sf::Time elapsed = clock.getElapsedTime();
    if (elapsed.asSeconds() >= spawnCooldown) {
        std::cout << "Cooldown ended" << std::endl;
        int laneNum = std::rand() % 7 + 1;  // random number of lanes
        std::cout << "LaneNum: " << laneNum << std::endl;
        setLaneNum(laneNum);
        std::cout << "Lane number set" << std::endl;
        clock.restart();
        // base spawn cooldown based on difficulty with randomness
        float difficultyFactor = game->difficulty;
        spawnCooldown = std::max(2.5f, 3.5f - difficultyFactor * 0.1f + static_cast<float>(rand()) / RAND_MAX * 0.5f);
        std::cout << "new spawnCooldown calculated as : " << spawnCooldown << std::endl;
        std::cout << "spawning enemies" << std::endl;
        for (int i = 0; i < laneNum; ++i) {
            std::cout << "spawning in lane: " << i << std::endl;

            float spawnX = lanePositions[i];
            float spawnY = 0.0f;

            std::cout << "position set to: " << spawnX << ", " << spawnY << std::endl;

            int baseHealth = 1;
            float baseSpeed = 1.0f;

            int health = baseHealth + static_cast<int>(difficultyFactor * 0.5f) + rand() % 2;
            float speed = baseSpeed + difficultyFactor * 0.1f + static_cast<float>(rand()) / RAND_MAX * 0.8f;
            float weaponCooldown = 1 / difficultyFactor + static_cast<float>(rand()) / RAND_MAX * 0.5f;

            std::cout << "enemy in lane: " << i << "health: " << health << "speed: " << speed << "weaponCooldown: " << weaponCooldown << std::endl;
            std::cout << game << std::endl;

            game->createBasicEnemy_Single(spawnX, spawnY, health, speed, weaponCooldown);
            std::cout << "enemy created" << std::endl;
        }
    }
}

void EnemyManager::setLaneNum(int laneNum) {
    float laneWidth = static_cast<float>(X_RES) / laneNum;

    lanePositions.resize(laneNum);

    for (int i = 0; i < laneNum; ++i) {
        float x = (i + 0.5f) * laneWidth;
        lanePositions[i] = x;
        std::cout << "lane: " << lanePositions[i] << " position: " << x << std::endl;
    }
}
