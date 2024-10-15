#ifndef PLAYER_H
#define PLAYER_H

#include "BoxObject.h"
#include "GameManager.h"
#include "Weapon.h"
#include "vector2.h"

class Player : public BoxObject {
   public:
    Player(GameManager* game);
    ~Player() override {};

    int health;
    float impulseStrength;
    float mass;
    float dampening;

    Weapon* currentWeapon;
    Vector2 velocity;

    void update(float gametime);
    void applyImpulse(Vector2 impulse);

    void shootWeapon();
};
#endif