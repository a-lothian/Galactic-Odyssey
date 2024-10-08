#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Weapon.h"

GameManager::GameManager()
    : window(sf::VideoMode(500, 800), "Galactic Odyssey", sf::Style::Default) {
    player = new Player();
}

void GameManager::renderGame() {
    this->window.clear();
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
        }

        // updateGame();
        renderGame();
    }
}
