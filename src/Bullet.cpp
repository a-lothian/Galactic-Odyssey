#include "Bullet.h"
#include "CircleObject.h"

Bullet::Bullet(GameManager* game, GameManager::Position pos, float radius)
    : CircleObject(game) {
    shape.setRadius(radius);
    SetPosition(pos);
    velocity.y = -20;
}

// Functions govern player movement, using physics
void Bullet::update(float gametime) {

    pos.y += velocity.y * gametime;
    shape.setPosition({pos.x, pos.y});
}
