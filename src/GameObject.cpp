#include "GameObject.h"
#include "GameManager.h"
#include <iostream>

GameObject::GameObject(GameManager* game)
    : game(game), pos({0, 0}), render(true), shape(nullptr) {
}

std::string GameObject::toString() const {
    return "DefaultObject";
}

bool GameObject::checkBoundingBox(GameObject* other) {  // Fast approximation of collision
    if (this->shape && other->shape) {
        return this->shape->getGlobalBounds().intersects(other->shape->getGlobalBounds());
    }
    return false;
}
