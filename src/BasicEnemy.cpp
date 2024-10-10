#include "BasicEnemy.h"

BasicEnemy::BasicEnemy(GameManager* game, GameManager::Position pos)
    : BoxObject(game), health(3), speed(2) {
}

BasicEnemy::~BasicEnemy()   {
    
}

void BasicEnemy::update(float gametime) {
    // kill if zero health
    if (health <= 0) {
        this->~BasicEnemy();
    }
    pos.y += speed;
}
