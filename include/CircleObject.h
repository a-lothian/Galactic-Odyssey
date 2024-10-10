#ifndef CIRCLEOBJECT_H
#define CIRCLEOBJECT_H

#include "GameObject.h"
#include "GameManager.h"

#include <SFML/Graphics.hpp>
#include <string>

class CircleObject : public GameObject {
   public:
    CircleObject(GameManager* game);                                                             // Debug Constructor
    CircleObject(GameManager* game, GameManager::Position pos, float radius, sf::Color colour);  // Main Constructor
    ~CircleObject() {};

    void SetPosition(GameManager::Position newPos) override;
    void drawObject() const override;
    std::string toString() const override;
    void update(float gametime) override {};
    bool isColliding(GameObject* other) override;

    float radius;

   protected:
    sf::CircleShape shape;
    sf::Color colour;
};

#endif
