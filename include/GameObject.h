#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "GameManager.h"
#include <iostream>
#include <vector>

class GameObject {
   public:
    GameObject(GameManager* parent);
    ~GameObject() {};

    virtual void SetPosition(Vector2 newPos) = 0;
    virtual void drawObject() const = 0;
    virtual std::string toString() const = 0;
    virtual void update(float gametime) = 0;

    virtual bool isColliding(GameObject* other) = 0;
    virtual void resolveCollision(GameObject* other) = 0;

    GameManager* game;
    Vector2 pos;
    bool render = true;
    Vector2 velocity;

    bool dynamic;    // can this object move other physics objects?
    bool receptive;  // does this object react to other physics objects?

    float mass;
    sf::Shape* shape;

    sf::Sprite sprite;
    sf::Texture texture;

    void initTexture(std::string filePath);
    void initSprite();
};

#endif