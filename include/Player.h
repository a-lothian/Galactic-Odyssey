#ifndef PLAYER_H
#define PLAYER_H

#define MOVEMENT_SPEED 10.0f

#include "GameObject.h"
#include "GameManager.h"

class Player : public GameObject {
   public:
    Player(GameManager* game);
    ~Player();

    GameManager::Position pos;

    int health;
    float moveSpeed = MOVEMENT_SPEED;

    void moveUP(float gametime);
    void moveDOWN(float gametime);
    void moveLEFT(float gametime);
    void moveRIGHT(float gametime);

    void shootWeapon();
};
#endif