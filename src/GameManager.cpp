#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Player.h"
#include "BasicEnemy.h"
#include "Weapon.h"
#include "BoxObject.h"

GameManager::GameManager()
    : window(sf::VideoMode(500, 800), "Galactic Odyssey", sf::Style::Titlebar | sf::Style::Close) {
    window.setKeyRepeatEnabled(true);
    player = new Player(this);
    objects.push_back(player);
    inputManager = new InputManager(player);
    initBackgroud();
}

void GameManager::initBackgroud() {
    if (!this->backgroundTexture.loadFromFile("assets/background.jpg")) {
        std::cout << "Error loading file." << std::endl;
    }
    this->backgroundTexture.setRepeated(true);
    this->backgroundSprite.setTexture(this->backgroundTexture);
    this->backgroundSprite.setOrigin(960, 500);
}
void GameManager::toString() {
    for (GameObject* object : objects) {
        std::cout << object->toString() << std::endl;
    }
}

void GameManager::renderGame() {
    this->window.clear();
    this->window.draw(this->backgroundSprite);
    for (GameObject* object : objects) {
        if (object->render) {
            object->drawObject();
        }
    }
    this->window.display();
    this->backgroundSprite.move(0, 0.5f);
}

void GameManager::createEnemy_Single(float x, float y) {
    enemy = new BasicEnemy(this, {x, y});
    objects.push_back(enemy);
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

void GameManager::HandleCollisions(float gametime, int substeps) {
    float sub_dt = gametime / substeps;

    for (int s = 0; s < substeps; s++) {
        for (u_long i = 0; i < objects.size(); i++) {
            objects[i]->update(sub_dt);
        }
        for (u_long i = 0; i < objects.size(); i++) {
            for (u_long j = i + 1; j < objects.size(); j++) {
                bool isColliding = objects[i]->isColliding(objects[j]);
                if (isColliding) {
                    objects[i]->resolveCollision(objects[j]);
                }
            }
        }
    }
}

void GameManager::updateGame() {
    /*
        General approach:
        1. Check inputs
        2. Do events (spawning stuff, AI logic, ect)
        3. Simulate objects (movement, collisions, ect)
    */

    // Handle input
    inputManager->CheckInputs();

    // Do events

    player->applyImpulse(inputManager->Direction);  // Move player

    for (u_long i = 0; i < objects.size(); i++) {  // simulate all objects 1 frame
    }

    // Check collisions + resolve collisions

    HandleCollisions(1, 8);  // 1 frame of
}
