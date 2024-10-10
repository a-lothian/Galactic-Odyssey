#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Player.h"
#include "BasicEnemy.h"
#include "Weapon.h"
#include "BoxObject.h"

GameManager::GameManager()
    : window(sf::VideoMode(500, 800), "Galactic Odyssey", sf::Style::Default) {
    window.setKeyRepeatEnabled(true);
    player = new Player(this);
    objects.push_back(player);
    inputManager = new InputManager(player);
}

void GameManager::toString() {
    for (GameObject* object : objects) {
        std::cout << object->toString() << std::endl;
    }
}

void GameManager::renderGame() {
    this->window.clear();
    for (GameObject* object : objects) {
        if (object->render) {
            object->drawObject();
        }
    }
    this->window.display();
}

void GameManager::createEnemy_Single(float x, float y) {
}

void GameManager::runGame() {
    framerate = 60;
    gamespeed = 1 / framerate;
    window.setFramerateLimit(framerate);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Update and render game
        updateGame();
        renderGame();
    }
}

void GameManager::checkCollisions() {
    for (u_long i = 0; i < objects.size(); i++) {
        for (u_long j = i + 1; j < objects.size(); j++) {
            bool isColliding = objects[i]->isColliding(objects[j]);

            if (isColliding) {
                std::cout << "Collision detected!" << std::endl;
            }
        }
    }
}

void GameManager::updateGame() {
    /*
        General approach:
        1. Check inputs
        2. Do events (spawning stuff, AI logic, ect)
        3. check collisions
        4. resolve collisions
    */

    // Handle input
    inputManager->CheckInputs();

    // Do events

    player->applyImpulse(inputManager->Direction);  // Move player

    for (u_long i = 0; i < objects.size(); i++) {  // simulate all objects 1 frame
        objects[i]->update(1);
    }

    // Check collisions

    checkCollisions();

    // Resolve collisions
    // TODO
}
