#ifndef CIRCLEOBJECT_H
#define CIRCLEOBJECT_H

#include "GameObject.h"
#include "GameManager.h"

#include <SFML/Graphics.hpp>
#include <string>

class CircleObject : public GameObject {
   public:
    CircleObject(GameManager* game);                                               // Debug Constructor
    CircleObject(GameManager* game, Vector2 pos, float radius, sf::Color colour);  // Main Constructor
    ~CircleObject() {};

    void SetPosition(Vector2 newPos) override;
    void drawObject() const override;
    std::string toString() const override;
    void update(float gametime) override;

    bool isColliding(GameObject* other) override;
    void resolveCollision(GameObject* other) override;

    bool isWithinBounds(int xres, int yres) override;

    float radius;

   protected:
    sf::CircleShape shape;
    sf::Color colour;
};

#endif
