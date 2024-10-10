#ifndef BULLET_H
#define BULLET_H

#include "CircleObject.h"
#include "GameManager.h"
#include "vector2.h"

class Bullet : public CircleObject {
   public:
    Bullet(GameManager* game, GameManager::Position pos, float radius, float speed, float angle, int damage, sf::Color colour);
    ~Bullet() {};

    Vector2 velocity;
    int damage;

    void update(float gametime);
};
#endif