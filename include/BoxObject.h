#ifndef BOXOBJECT_H
#define BOXOBJECT_H

#include "GameObject.h"
#include "GameManager.h"

#include <SFML/Graphics.hpp>
#include <string>

class BoxObject : public GameObject {
   public:
    BoxObject(GameManager* game);                                                                          // Debug Constructor
    BoxObject(GameManager* game, GameManager::Position pos, float width, float height, sf::Color colour);  // Main Constructor
    ~BoxObject() {};

    void SetPosition(GameManager::Position newPos) override;
    void drawObject() const override;
    std::string toString() const override;
    void update(float gametime) override {};

   protected:
    sf::RectangleShape shape;
    float width;
    float height;
    sf::Color colour;
};

#endif
