#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "vector2.h"

class Player;  // Ok had to add forward declaration back in

class InputManager {
   public:
    InputManager() {};
    InputManager(Player* p)
        : player(p) {}
    ~InputManager() {};

    Vector2 Direction;

    void CheckInputs();

   public:
    Player* player;
    bool up, down, left, right, space;
};

#endif