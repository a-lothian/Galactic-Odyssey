#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Player;

class InputManager {
   public:
    InputManager();
    ~InputManager() {};

    Player * playerReference;

    bool up, down, left, right;

    void inputFunction(sf::Keyboard::Key key, bool isPressed);

   private:
};


#endif