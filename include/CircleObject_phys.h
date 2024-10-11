#ifndef CIRCLEOBJECTPHYS_H
#define CIRCLEOBJECTPHYS_H

#include "GameObject.h"
#include "GameManager.h"

#include <SFML/Graphics.hpp>
#include <string>

class CircleObject_phys : public GameObject {
   public:
    CircleObject_phys(GameManager* game);                                               // Debug Constructor
    CircleObject_phys(GameManager* game, Vector2 pos, float radius, sf::Color colour);  // Main Constructor
    ~CircleObject_phys() {};

    void SetPosition(Vector2 newPos) override;
    void drawObject() const override;
    std::string toString() const override;
    void update(float gametime) override;

    bool isColliding(GameObject* other) override;
    void resolveCollision(GameObject* other) override;

    float radius;

   protected:
    sf::CircleShape shape;
    sf::Color colour;
};

#endif
