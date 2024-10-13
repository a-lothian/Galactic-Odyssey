#include "GameObject.h"
#include "GameManager.h"
#include <iostream>

GameObject::GameObject(GameManager* game)
    : game(game), pos({0, 0}), render(true), velocity({0, 0}), mass(1), shape(nullptr) {
}

void GameObject::initTexture(std::string filePath)   {
    if (!this->texture.loadFromFile(filePath))  {
        std::cout << "Error loading file." << std::endl;
    }
}

void GameObject::initSprite()    {
    this->sprite.setTexture(this->texture);
}

std::string GameObject::toString() const {
    return "DefaultObject";
}