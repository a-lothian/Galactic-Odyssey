#include "InputManager.h"
#include "Player.h"
#include "vector"

void InputManager::inputFunction() {
    // NOTE: the origin is top left with Y increasing downwards, so up is negative.
    // Reset direction
    Direction.x = 0;
    Direction.y = 0;

    // Check if the keys are currently pressed
    up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

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

    Direction = Direction.normalize();  // strafing shouldn't be faster
}