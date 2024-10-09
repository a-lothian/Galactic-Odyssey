#include "Player.h"

Player::Player(GameManager* game)
    : BoxObject(game), health(100), moveSpeed(1.0f) {
    pos.x = 0;
    pos.y = 0;
}

void Player::moveUP(float gametime) {
    pos.y -= moveSpeed * gametime;
}

void Player::moveDOWN(float gametime) {
    pos.y += moveSpeed * gametime;
}

void Player::moveLEFT(float gametime) {
    pos.x -= moveSpeed * gametime;
}

void Player::moveRIGHT(float gametime) {
    pos.x += moveSpeed * gametime;
}