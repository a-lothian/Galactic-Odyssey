#include "Bullet.h"
#include "CircleObject.h"

#include <cmath>

Bullet::Bullet(GameManager* game, GameObject* parent, Vector2 pos, float radius, float speed, float angle, int damage, sf::Color colour)
    : CircleObject(game, pos, radius, colour), parent(parent), damage(damage) {
    toDelete = false;
    if (game == nullptr) {
        std::cerr << "Error: GameManager is null! in bullet" << std::endl;
    }
    if (parent == nullptr) {
        std::cerr << "Error: Bullet parent is null!" << std::endl;
    }

    float angleRadians = (angle) * (M_PI / 180.0f);  // convert to radians

    velocity.x = speed * std::cos(angleRadians);
    velocity.y = -speed * std::sin(angleRadians);
    isPhysics = false;
}

// Handles bullet movement

void Bullet::update(float gametime) {
    pos.x += velocity.x * gametime;
    pos.y += velocity.y * gametime;
    shape.setPosition({pos.x, pos.y});
}
