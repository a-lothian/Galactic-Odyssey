#include "Player.h"

Player::Player(GameManager* game)
    : BoxObject(game), health(100), moveSpeed(15.0f) {
    pos.x = 0;
    pos.y = 0;
}

// Functions govern player movement

void Player::moveUP(float gametime) {
    pos.y -= moveSpeed * gametime;
    shape.setPosition({pos.x, pos.y});
}

void Player::moveDOWN(float gametime) {
    pos.y += moveSpeed * gametime;
    shape.setPosition({pos.x, pos.y});
}

void Player::moveLEFT(float gametime) {
    pos.x -= moveSpeed * gametime;
    shape.setPosition({pos.x, pos.y});
}

void Player::moveRIGHT(float gametime) {
    pos.x += moveSpeed * gametime;
    shape.setPosition({pos.x, pos.y});
}


