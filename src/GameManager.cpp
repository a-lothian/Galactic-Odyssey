#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Weapon.h"
#include "BoxObject.h"

GameManager::GameManager()
    : window(sf::VideoMode(500, 800), "Galactic Odyssey", sf::Style::Default) {
    window.setKeyRepeatEnabled(true);
    player = new Player(this);
    objects.push_back(player);
    inputManager = new InputManager;
    inputManager->playerReference = player;
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

        // Handle input
        inputManager->inputFunction();

        // Update and render game
        updateGame();
        renderGame();
    }
}

void GameManager::updateGame() {
    // Pass Vector for impulse instead of if-else
    player->applyImpulse(inputManager->Direction);
    player->update(1);
}
