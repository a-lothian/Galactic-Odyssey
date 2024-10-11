#ifndef BOXOBJECTPHYS_H
#define BOXOBJECTPHYS_H

#include "GameObject.h"
#include "GameManager.h"

#include <SFML/Graphics.hpp>
#include <string>

class BoxObject_phys : public GameObject {
   public:
    BoxObject_phys(GameManager* game);                                                            // Debug Constructor
    BoxObject_phys(GameManager* game, Vector2 pos, float width, float height, sf::Color colour);  // Main Constructor
    ~BoxObject_phys() {};

    void SetPosition(Vector2 newPos) override;
    void drawObject() const override;
    std::string toString() const override;
    void update(float gametime) override;

    bool isColliding(GameObject* other) override;
    void resolveCollision(GameObject* other) override;

    float width;
    float height;

   protected:
    sf::RectangleShape shape;
    sf::Color colour;
};

#endif
