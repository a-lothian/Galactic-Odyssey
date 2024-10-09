#include "InputManager.h"
#include "Player.h"

InputManager::InputManager() {
}

void InputManager::inputFunction(sf::Keyboard::Key key, bool isPressed) {
    if (isPressed == true) { // When keystrokes are recognised via events, booleans change accordingly
        if (key == sf::Keyboard::Up) {
            up = true;
        } if (key == sf::Keyboard::Down) {
            down = true;
        } if (key == sf::Keyboard::Left) {
            left = true;
        } if (key == sf::Keyboard::Right) {
            right = true;
        }
    }     if (isPressed == false) {
        if (key == sf::Keyboard::Up) {
            up = false;
        } if (key == sf::Keyboard::Down) {
            down = false;
        } if (key == sf::Keyboard::Left) {
            left = false;
        } if (key == sf::Keyboard::Right) {
            right = false;
        }
}
}
