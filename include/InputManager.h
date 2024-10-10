#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "vector2.h"

class InputManager {
   public:
    InputManager() {};
    ~InputManager() {};

    Vector2 Direction;

    void CheckInputs();

   private:
   bool up, down, left, right;
};

#endif