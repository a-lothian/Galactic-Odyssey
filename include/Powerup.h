#ifndef POWERUP_H
#define POWERUP_H

#include "BoxObject.h"
#include "GameManager.h"
#include "vector2.h"

class Powerup : public BoxObject {
   public:
    Powerup(GameManager* game, Vector2 pos);
    ~Powerup() {}

    Vector2 velocity;

    void update(float gametime);
};

#endif