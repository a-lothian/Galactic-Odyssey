#ifndef BASIC_ENEMY_H
#define BASIC_ENEMY_H

#include "BoxObject.h"
#include "GameManager.h"
#include "Weapon.h"
#include "vector2.h"

class BasicEnemy : public BoxObject {
   public:
    BasicEnemy(GameManager* game, Vector2 pos, int health, float speed, float weaponCooldown);
    ~BasicEnemy() {};

    int health;
    float speed;

    Weapon* currentWeapon;
    Vector2 pos;
    Vector2 velocity;

    void update(float gametime);
};
#endif