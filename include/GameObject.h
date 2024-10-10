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

    virtual void SetPosition(Position newPos) = 0;
    virtual void drawObject() const = 0;
    virtual std::string toString() const = 0;
    virtual void update(float gametime) = 0;

    bool checkBoundingBox(GameObject* other);

    GameManager* game;
    Position pos;
    bool render = true;
    sf::Shape* shape;
};

#endif