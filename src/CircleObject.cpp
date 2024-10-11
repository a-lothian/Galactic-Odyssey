#include "CircleObject.h"
#include "BoxObject.h"

#include <cmath>

CircleObject::CircleObject(GameManager* game)  // Default Debug Constructor
    : GameObject(game), radius(25), shape(sf::CircleShape(25)), colour(sf::Color::Red) {
    shape.setPosition(pos.x - radius, pos.y - radius);
}

CircleObject::CircleObject(GameManager* game, Vector2 pos, float radius, sf::Color colour)
    : GameObject(game), radius(radius), colour(colour) {
    this->pos = pos;  // Assign the inherited 'pos' from GameObject
    shape.setRadius(radius);
    shape.setPosition(pos.x - radius, pos.y - radius);
    shape.setFillColor(colour);
}

void CircleObject::drawObject() const {
    game->window.draw(shape);
}

void CircleObject::SetPosition(Vector2 newPos) {
    pos.x = newPos.x;  // 'pos' is inherited from GameObject
    pos.y = newPos.y;
    shape.setPosition(pos.x - radius, pos.y - radius);
}

std::string CircleObject::toString() const {
    return "CircleObject";
}

void CircleObject::update(float gametime) {
    pos.y += velocity.y * gametime;
    pos.x += velocity.x * gametime;
    shape.setPosition({pos.x - radius, pos.y - radius});  // technical debt here. not sure why subtraction is needed
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

void CircleObject::resolveCollision(GameObject* other) {
    float distance = std::sqrt(pos.x - other->pos.x * pos.x - other->pos.x + pos.y - other->pos.y * pos.y - other->pos.y);

    if (dynamic_cast<CircleObject*>(other)) {  // Ball vs Ball

        CircleObject* otherBall = (CircleObject*)other;

        float totalradii = this->radius + otherBall->radius;
        float overlap = (this->radius + otherBall->radius) - distance;
        Vector2 o1_o2 = this->pos - other->pos;
        Vector2 normal = o1_o2 * (1 / distance);

        float o1Response = overlap / totalradii;
        float o2Response = overlap / totalradii;

        Vector2 correction = normal * overlap;

        this->pos = this->pos + (correction * o1Response);
        other->pos = other->pos + ((correction * -1) * o2Response);

        // relative velocity
        Vector2 relativeVelocity = other->velocity - this->velocity;
        float velocityAlongNormal = relativeVelocity.dot(normal);

        // only reflect if objects are moving towards each other
        if (velocityAlongNormal > 0) {
            float bounciness = 0.8f;

            // Calculate impulse scalar
            float impulseScalar = -(1 + bounciness) * velocityAlongNormal;
            impulseScalar /= (1 / this->mass + 1 / other->mass);

            // Apply impulse
            Vector2 impulse = normal * impulseScalar;
            this->velocity = this->velocity - impulse * (1 / this->mass);
            other->velocity = other->velocity + impulse * (1 / other->mass);
        }
    } else if (dynamic_cast<BoxObject*>(other)) {
        BoxObject* otherBox = (BoxObject*)other;

        float halfWidth = otherBox->width / 2;
        float halfHeight = otherBox->height / 2;

        // Find the closest point on the AABB to the ball's center
        float closestX = std::max(otherBox->pos.x - halfWidth, std::min(this->pos.x, other->pos.x + halfWidth));
        float closestY = std::max(otherBox->pos.y - halfHeight, std::min(this->pos.y, other->pos.y + halfHeight));

        Vector2 closestPoint(closestX, closestY);
        Vector2 ballToBox = this->pos - closestPoint;

        float distance = ballToBox.length();
        float overlap = this->radius - distance;

        // If no overlap, no collision
        if (overlap <= 0) {
            return;
        }

        // Normalize the collision normal
        Vector2 normal = ballToBox * (1.0f / distance);

        float totalMass = this->mass + other->mass;
        float ballResponse = this->mass / totalMass;
        float aabbResponse = other->mass / totalMass;

        // Position correction
        Vector2 correction = normal * overlap;
        this->pos = this->pos + (correction * ballResponse);
        other->pos = other->pos - (correction * aabbResponse);

        // Relative velocity
        Vector2 relativeVelocity = this->velocity - other->velocity;
        float velocityAlongNormal = relativeVelocity.dot(normal);

        // Only reflect if objects are moving towards each other
        if (velocityAlongNormal < 0) {
            float bounciness = 0.8f;  // Coefficient of restitution

            // Calculate impulse scalar
            float impulseScalar = -(1 + bounciness) * velocityAlongNormal;
            impulseScalar /= (1 / this->mass + 1 / other->mass);

            // Apply impulse
            Vector2 impulse = normal * impulseScalar;
            this->velocity = this->velocity + impulse * (1 / this->mass);
            other->velocity = other->velocity - impulse * (1 / other->mass);
        }
    }

    else {
        velocity = Vector2(0, 0);
        std::cout << "Collision type not implemented, not ball vs ball\n";
    }
}
