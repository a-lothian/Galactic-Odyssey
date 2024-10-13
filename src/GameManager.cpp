#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Player.h"
#include "BasicEnemy.h"
#include "Weapon.h"
#include "BoxObject.h"
#include <fstream>
#include <string>

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
                saveGame();
                window.close();
            }
        }

        // Update and render game
        updateGame();
        renderGame();
    }
}

void GameManager::saveGame() {
    std::ofstream user_save;
    user_save.open("saves/user_save");
    if (!user_save.is_open()) {
        std::cerr << "The saves directory could not be accessed. Game failed to save. \n";
    } else {
        // Will store the name of the player (assuming we ask for name at the start) and their score
        user_save << "score=" << score << std::endl;
        // user_save << "name=" << name << std::endl;
        user_save.close();
    }
}

void GameManager::loadSave() {
    std::ifstream user_load;
    user_load.open("saves/user_save");
    if (!user_load.is_open()) {
        std::cout << "No save detected. \n";
        score = 0; // If there is no save, sets score to 0
    } else {
        // Loads player score
        std::string score_str;
        user_load >> score_str;
        score_str = score_str.substr(6); // Removing the "score=" part from the line
        score = std::stoi(score_str);
        user_load.close();
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



