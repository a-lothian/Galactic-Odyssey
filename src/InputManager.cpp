#include "InputManager.h"
#include "Player.h"

void InputManager::inputFunction(sf::Keyboard::Key key, bool isPressed) {
    switch (key) {  // When keystrokes are recognised via events, booleans change accordingly
    case sf::Keyboard::Up:
        up = isPressed;
        break;
    case sf::Keyboard::Down:
        down = isPressed;
        break;
    case sf::Keyboard::Left:
        left = isPressed;
        break;
    case sf::Keyboard::Right:
        right = isPressed;
        break;
    default:
        break;
    }
}