#ifndef PLAYER_H
#define PLAYER_H

#include "BoxObject.h"
#include "GameManager.h"
#include "vector2.h"

class Player : public BoxObject {
   public:
    Player(GameManager* game);
    ~Player();

    int health;
    float impulseStrength;
    float mass;
    float dampening;
    Vector2 velocity;

    void update(float gametime);
    void applyImpulse(Vector2 impulse);

    void moveUP(float gametime);
    void moveDOWN(float gametime);
    void moveLEFT(float gametime);
    void moveRIGHT(float gametime);
    void inputFunction(sf::Keyboard::Key key, bool isPressed);

    void shootWeapon();
};
#endif