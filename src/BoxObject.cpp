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

void BoxObject::initTexture(std::string filePath)   {
    if (!this->texture.loadFromFile(filePath))  {
        std::cout << "Error loading file." << std::endl;
    }
}

void BoxObject::initSprite()    {
    this->sprite.setTexture(this->texture);
    this->sprite.scale(0.09f,0.09f);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width * 4, this->sprite.getGlobalBounds().height * 4);
}

void BoxObject::drawObject() const {
    game->window.draw(shape);
    game->window.draw(this->sprite);
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

void BoxObject::resolveCollision(GameObject* other) {
    if (dynamic_cast<BoxObject*>(other)) {
        BoxObject* otherBox = (BoxObject*)other;

        float halfWidth = width / 2;
        float halfHeight = height / 2;
        float otherhalfWidth = otherBox->width / 2;
        float otherhalfHeight = otherBox->height / 2;

        // Calculate overlap in both x and y directions
        float overlapX = (halfWidth + otherhalfWidth) - std::abs(this->pos.x - other->pos.x);
        float overlapY = (halfHeight + otherhalfHeight) - std::abs(this->pos.y - other->pos.y);

        // If no overlap, no collision
        if (overlapX <= 0 || overlapY <= 0) {
            return;
        }

        // Find the axis of the smallest overlap
        float overlap;
        Vector2 normal;
        if (overlapX < overlapY) {
            overlap = overlapX;
            normal = (this->pos.x < other->pos.x) ? Vector2(-1, 0) : Vector2(1, 0);
        } else {
            overlap = overlapY;
            normal = (this->pos.y < other->pos.y) ? Vector2(0, -1) : Vector2(0, 1);
        }

        // Calculate the response ratio
        float totalMass = this->mass + other->mass;
        float thisResponse = this->mass / totalMass;
        float otherResponse = other->mass / totalMass;

        // Correct positions based on the smallest overlap
        Vector2 correction = normal * overlap;
        this->pos = this->pos + (correction * thisResponse);
        other->pos = other->pos - (correction * otherResponse);

        // Relative velocity
        Vector2 relativeVelocity = other->velocity - this->velocity;
        float velocityAlongNormal = relativeVelocity.dot(normal);

        // Only reflect if objects are moving towards each other
        if (velocityAlongNormal > 0) {
            float bounciness = 0.8f;  // Coefficient of restitution

            // Calculate impulse scalar
            float impulseScalar = -(1 + bounciness) * velocityAlongNormal;
            impulseScalar /= (1 / this->mass + 1 / other->mass);

            // Apply impulse
            Vector2 impulse = normal * impulseScalar;
            this->velocity = this->velocity - impulse * (1 / this->mass);
            other->velocity = other->velocity + impulse * (1 / other->mass);
        }
    } else if (dynamic_cast<CircleObject*>(other)) {
        CircleObject* otherBall = (CircleObject*)other;

        float halfWidth = width / 2;
        float halfHeight = height / 2;

        // Find the closest point on the AABB to the ball's center
        float closestX = std::max(this->pos.x - halfWidth, std::min(otherBall->pos.x, this->pos.x + halfWidth));
        float closestY = std::max(this->pos.y - halfHeight, std::min(otherBall->pos.y, this->pos.y + halfHeight));

        Vector2 closestPoint(closestX, closestY);
        Vector2 ballToBox = otherBall->pos - closestPoint;

        float distance = ballToBox.length();
        float overlap = otherBall->radius - distance;

        // If no overlap, no collision
        if (overlap <= 0) {
            return;
        }

        // Normalize the collision normal
        Vector2 normal = ballToBox * (1.0f / distance);

        float totalMass = this->mass + other->mass;
        float aabbResponse = this->mass / totalMass;
        float ballResponse = other->mass / totalMass;

        // Position correction
        Vector2 correction = normal * overlap;
        this->pos = this->pos - (correction * aabbResponse);
        other->pos = other->pos + (correction * ballResponse);

        // Relative velocity
        Vector2 relativeVelocity = other->velocity - this->velocity;
        float velocityAlongNormal = relativeVelocity.dot(normal);

        // Only reflect if objects are moving towards each other
        if (velocityAlongNormal > 0) {
            float bounciness = 0.8f;  // Coefficient of restitution

            // Calculate impulse scalar
            float impulseScalar = -(1 + bounciness) * velocityAlongNormal;
            impulseScalar /= (1 / this->mass + 1 / other->mass);

            // Apply impulse
            Vector2 impulse = normal * impulseScalar;
            this->velocity = this->velocity - impulse * (1 / this->mass);
            other->velocity = other->velocity + impulse * (1 / other->mass);
        }
    } else {
        std::cout << "Collision type not implemented\n";
    }
}
