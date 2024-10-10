#include "Bullet.h"
#include "CircleObject.h"

#include <cmath>

Bullet::Bullet(GameManager* game, GameManager::Position pos, float radius, float speed, float angle, int damage, sf::Color colour)
    : CircleObject(game, pos, radius, colour), damage(damage) {
    float angleRadians = (angle + 90) * (M_PI / 180.0f);  // convert to radians

    velocity.x = speed * std::cos(angleRadians);
    velocity.y = -speed * std::sin(angleRadians);
}

// Handles bullet movement

void Bullet::update(float gametime) {
    pos.x += velocity.x * gametime;
    pos.y += velocity.y * gametime;
    shape.setPosition({pos.x, pos.y});
}
