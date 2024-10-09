#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "GameManager.h"
#include <iostream>
#include <vector>

class GameObject {
   public:
    GameObject(GameManager* parent);
    ~GameObject() {};

    GameManager* game;
    GameManager::Position pos;
    bool render = true;
};

#endif