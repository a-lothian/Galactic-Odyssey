#ifndef BULLET_H
#define BULLET_H

#include "CircleObject.h"
#include "GameManager.h"
#include "vector2.h"

class Bullet : public CircleObject {
   public:
    GameObject* parent;
    int damage;
    Vector2 velocity;

    Bullet(GameManager* game, GameObject* parent, Vector2 pos, float radius, float speed, float angle, int damage, sf::Color colour);
    ~Bullet() {};

    void update(float gametime);
};

#endif