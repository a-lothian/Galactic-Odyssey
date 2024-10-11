#ifndef BOXOBJECT_H
#define BOXOBJECT_H

#include "GameObject.h"
#include "GameManager.h"

#include <SFML/Graphics.hpp>
#include <string>

class BoxObject : public GameObject {
   public:
    BoxObject(GameManager* game);                                                            // Debug Constructor
    BoxObject(GameManager* game, Vector2 pos, float width, float height, sf::Color colour);  // Main Constructor
    ~BoxObject() {};

    sf::Sprite sprite;
    sf::Texture texture;

    void initTexture(std::string filePath);
    void initSprite();

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
