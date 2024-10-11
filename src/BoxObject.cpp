#include "BoxObject.h"
#include "CircleObject.h"

BoxObject::BoxObject(GameManager* game)  // Default Debug Constructor
    : GameObject(game), width(25), height(25), shape(sf::Vector2f(width, height)), colour(sf::Color::Red) {
}

BoxObject::BoxObject(GameManager* game, Vector2 pos, float width, float height, sf::Color colour)
    : GameObject(game), width(width), height(height), colour(colour) {
    this->pos = pos;
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(pos.x - (width / 2), pos.y - (height / 2));
    shape.setFillColor(colour);
}

void BoxObject::drawObject() const {
    game->window.draw(shape);
}

void BoxObject::SetPosition(Vector2 newPos) {
    pos.x = newPos.x;  // 'pos' is inherited from GameObject
    pos.y = newPos.y;
    shape.setPosition(pos.x - (width / 2), pos.y - (height / 2));
}

std::string BoxObject::toString() const {
    return "BoxObject";
}

void BoxObject::update(float gametime) {
    pos.y += velocity.y * gametime;
    pos.x += velocity.x * gametime;
    shape.setPosition({pos.x - (width / 2), pos.y - (height / 2)});  // technical debt here. not sure why subtraction is needed
}

bool BoxObject::isColliding(GameObject* other) {
    Vector2 offset = {pos.x - other->pos.x, pos.y - other->pos.y};
    Vector2 halfsize = {width / 2, height / 2};

    if (dynamic_cast<BoxObject*>(other)) {  // BoxObject -> BoxObject Collision
        BoxObject* otherBox = static_cast<BoxObject*>(other);
        Vector2 otherhalfsize = Vector2(otherBox->width / 2, otherBox->height / 2);

        bool xcollide = std::abs(offset.x) < (halfsize.x + otherhalfsize.x);
        bool ycollide = std::abs(offset.y) < (halfsize.y + otherhalfsize.y);

        if (xcollide && ycollide) {
            return true;
        }
    } else if (dynamic_cast<CircleObject*>(other))  // BoxObject -> CircleObject Collision
    {
        CircleObject* otherBall = static_cast<CircleObject*>(other);

        Vector2 closestPoint;
        closestPoint.x = std::max(pos.x - halfsize.x, std::min(otherBall->pos.x, pos.x + halfsize.x));
        closestPoint.y = std::max(pos.y - halfsize.y, std::min(otherBall->pos.y, pos.y + halfsize.y));

        Vector2 difference = {closestPoint.x - other->pos.x, closestPoint.y - other->pos.y};
        float distanceSquared = difference.dot(difference);
        float radiusSquared = otherBall->radius * otherBall->radius;

        if (distanceSquared < radiusSquared) {
            return true;
        }
    }

    // No collision
    return false;
}
