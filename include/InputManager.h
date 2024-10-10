#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "vector2.h"

class Player;

class InputManager {
   public:
    InputManager() {};
    ~InputManager() {};

    Player* playerReference;

    bool up, down, left, right;

    Vector2 Direction;

    void inputFunction();
    void clearInput();

   private:
};

#endif