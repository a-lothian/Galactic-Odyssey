#include "BoxObject.h"

BoxObject::BoxObject(GameManager* game)  // Default Debug Constructor
    : GameObject(game), game(game), shape(sf::Vector2f(25, 25)), width(50), height(50), colour(sf::Color::Red) {
}

BoxObject::BoxObject(GameManager* game, GameManager::Position pos, float height, float width, sf::Color colour)
    : GameObject(game), game(game), pos(pos), width(width), height(height), colour(colour) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(pos.x - (width / 2), pos.y - (height / 2));
    shape.setFillColor(colour);
}

void BoxObject::drawObject() const {
    game->window.draw(shape);
}
