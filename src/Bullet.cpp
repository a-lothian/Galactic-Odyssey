#include "Bullet.h"
#include "CircleObject.h"

Bullet::Bullet(GameManager* game, GameManager::Position pos, float radius, sf::Color colour)
    : CircleObject(game, pos, radius, colour) {
    velocity.y = -20;
}

// Handles bullet movement

void Bullet::update(float gametime) {

    pos.y += velocity.y * gametime;
    shape.setPosition({pos.x, pos.y});
}
