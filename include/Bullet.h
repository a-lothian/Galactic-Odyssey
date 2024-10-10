#ifndef BULLET_H
#define BULLET_H

#include "CircleObject.h"
#include "GameManager.h"
#include "vector2.h"

class Bullet : public CircleObject {
   public:
    Bullet(GameManager* game, GameManager::Position pos, float radius);
    ~Bullet();

    Vector2 velocity;

    void update(float gametime);
};
#endif