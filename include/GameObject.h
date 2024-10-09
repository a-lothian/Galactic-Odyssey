#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "GameManager.h"
#include <iostream>
#include <vector>

typedef GameManager::Position Position;

class GameObject {
   public:
    GameObject(GameManager* parent);
    ~GameObject() {};

    virtual void drawObject() const = 0;

    GameManager* game;
    Position pos;
    bool render = true;
};

#endif