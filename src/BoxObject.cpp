#include "BoxObject.h"

BoxObject::BoxObject(GameManager* game)  // Default Debug Constructor
    : GameObject(game), shape(sf::Vector2f(25, 25)), width(50), height(50), colour(sf::Color::Red) {
}

BoxObject::BoxObject(GameManager* game, GameManager::Position pos, float width, float height, sf::Color colour)
    : GameObject(game), width(width), height(height), colour(colour) {
    this->pos = pos;
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(pos.x - (width / 2), pos.y - (height / 2));
    shape.setFillColor(colour);
}

void BoxObject::drawObject() const {
    game->window.draw(shape);
}

void BoxObject::SetPosition(GameManager::Position newPos) {
    pos.x = newPos.x;  // 'pos' is inherited from GameObject
    pos.y = newPos.y;
    shape.setPosition(pos.x - (width / 2), pos.y - (height / 2));
}

std::string BoxObject::toString() const {
    return "BoxObject";
}

