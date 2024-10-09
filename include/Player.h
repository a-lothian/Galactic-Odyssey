#ifndef PLAYER_H
#define PLAYER_H

#define MOVEMENT_SPEED 10.0f

#include "BoxObject.h"
#include "GameManager.h"

class Player : public BoxObject {
   public:
    Player(GameManager* game);
    ~Player();

    

    int health;
    float moveSpeed = MOVEMENT_SPEED;

    void moveUP(float gametime);
    void moveDOWN(float gametime);
    void moveLEFT(float gametime);
    void moveRIGHT(float gametime);
    void inputFunction(sf::Keyboard::Key key, bool isPressed);

    void shootWeapon();
};
#endif