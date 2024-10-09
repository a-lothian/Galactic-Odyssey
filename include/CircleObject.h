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

   protected:
    sf::CircleShape shape;
    float radius;
    sf::Color colour;
};

#endif
