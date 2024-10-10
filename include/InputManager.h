#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Player;

class InputManager {
   public:
    InputManager() {};
    ~InputManager() {};

    struct Direction {
        float dx = 0;
        float dy = 0;
    };

    Player* playerReference;

    bool up, down, left, right;

    Direction Direction;

    void inputFunction(sf::Keyboard::Key key, bool isPressed);

   private:
};

#endif