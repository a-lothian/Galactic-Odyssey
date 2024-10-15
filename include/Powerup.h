#ifndef POWERUP_H
#define POWERUP_H

#include "BoxObject.h"
#include "GameManager.h"
#include "vector2.h"

class Powerup : public BoxObject {
   public:
    enum powerupType {  // Powerup types
        ADDBULLET,
        FIRERATE,
        DAMAGE
    };

    Powerup(GameManager* game, powerupType power, Vector2 pos);
    ~Powerup() {}

    float speed;
    powerupType power;

    Vector2 pos;

    void update(float gametime);
};

#endif