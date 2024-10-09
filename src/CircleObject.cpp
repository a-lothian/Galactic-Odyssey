#include "CircleObject.h"

CircleObject::CircleObject(GameManager* game)  // Default Debug Constructor
    : GameObject(game), shape(sf::CircleShape(25)), radius(25), colour(sf::Color::Red) {
    shape.setPosition(0, 0);
}

CircleObject::CircleObject(GameManager* game, GameManager::Position pos, float radius, sf::Color colour)
    : GameObject(game), radius(radius), colour(colour) {
    this->pos = pos;  // Assign the inherited 'pos' from GameObject
    shape.setRadius(radius);
    shape.setPosition(pos.x - radius, pos.y - radius);
    shape.setFillColor(colour);
}

void CircleObject::drawObject() const {
    game->window.draw(shape);
}

void CircleObject::SetPosition(GameManager::Position newPos) {
    pos.x = newPos.x;  // 'pos' is inherited from GameObject
    pos.y = newPos.y;
    shape.setPosition(pos.x - radius, pos.y - radius);
}

std::string CircleObject::toString() const {
    return "CircleObject";
}
