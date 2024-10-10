#include "CircleObject.h"
#include "BoxObject.h"

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

bool CircleObject::isColliding(GameObject* other) {
    if (dynamic_cast<CircleObject*>(other))  // CircleObject -> CircleObject Collision
    {
        CircleObject* otherball = (CircleObject*)other;  // cast to CircleObject
        float radii_sum = this->radius + otherball->radius;

        float distance = std::sqrt(pos.x - otherball->pos.x * pos.x - otherball->pos.x + pos.y - otherball->pos.y * pos.y - otherball->pos.y);

        if (distance <= radii_sum) {
            return true;
        }

    } else if (dynamic_cast<BoxObject*>(other))  // CircleObject -> BoxObject Collision
    {
        BoxObject* otherBox = (BoxObject*)other;
        Vector2 otherhalfsize = Vector2(otherBox->width / 2, otherBox->height / 2);
        bool xcollide = std::abs(pos.x - otherBox->pos.x) < (this->radius + otherhalfsize.x);
        bool ycollide = std::abs(pos.y - otherBox->pos.y) < (this->radius + otherhalfsize.y);
        if (xcollide && ycollide) {
            return true;
        }
    }
    return false;
}
