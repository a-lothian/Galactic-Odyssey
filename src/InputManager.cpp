#include "InputManager.h"
#include "Player.h"
#include "vector"

class Player;

void InputManager::CheckInputs() {
    // NOTE: the origin is top left with Y increasing downwards, so up is negative.
    // Reset direction
    Direction.x = 0;
    Direction.y = 0;

    // Check if the keys are currently pressed
    up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

    if (up) {
        Direction.y -= 1;
    }
    if (down) {
        Direction.y += 1;
    }
    if (left) {
        Direction.x -= 1;
    }
    if (right) {
        Direction.x += 1;
    }
    if (space) {
        player->shootWeapon();
    }

    Direction = Direction.normalize();  // strafing shouldn't be faster
}
