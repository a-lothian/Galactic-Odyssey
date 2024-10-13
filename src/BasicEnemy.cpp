#include "BasicEnemy.h"

BasicEnemy::BasicEnemy(GameManager* game, Vector2 pos)
    : BoxObject(game), health(3), speed(2) {
        initTexture("assets/enemy1.png");
        initSprite();
        sprite.scale(0.2f, 0.2f);
        sprite.setOrigin(190, 100);
        shape.setPosition({pos.x, pos.y});
        sprite.setPosition({pos.x, pos.y});
}

void BasicEnemy::update(float gametime) {
    pos.y += speed * gametime;

    shape.setPosition({pos.x, pos.y});
    sprite.setPosition({pos.x, pos.y});
}
