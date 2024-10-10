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
        window.setFramerateLimit(framerate);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {  // Accessing InputManager
                inputManager->inputFunction(event.key.code, true);
            }
            if (event.type == sf::Event::KeyReleased) {
                inputManager->inputFunction(event.key.code, false);
            }
        }
        updateGame();
        renderGame();
    }
}

void GameManager::updateGame() {
    // Function should call player movement methods

    if (inputManager->up) {
        player->moveUP(1);
    }
    if (inputManager->down) {
        player->moveDOWN(1);
    }
    if (inputManager->left) {
        player->moveLEFT(1);
    }
    if (inputManager->right) {
        player->moveRIGHT(1);
    }
}
