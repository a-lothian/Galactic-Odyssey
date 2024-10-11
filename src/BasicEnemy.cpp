#include "BasicEnemy.h"

BasicEnemy::BasicEnemy(GameManager* game, Vector2 pos)
    : BoxObject(game), health(3), speed(2) {
}

void BasicEnemy::update(float gametime) {
    pos.y += speed * gametime;
}
