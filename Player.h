#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : public GameObject {
   public:
    Player();
    ~Player();

    float moveSpeed;

    void moveUP();
    void moveDOWN();
    void moveLEFT();
    void moveRIGHT();
};
#endif