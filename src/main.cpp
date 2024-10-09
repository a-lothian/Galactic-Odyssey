#include <iostream>
#include "GameManager.h"
#include <SFML/Graphics.hpp>
#include "BoxObject.h"

#define X_RES 500
#define Y_RES 800

int main() {
    GameManager gameManager;
    BoxObject box(&gameManager, {250, 400}, 100, 100, sf::Color::Red);  // red box in middle of screen
    gameManager.objects.push_back(&box);
    box.SetPosition({100, 100});
    gameManager.runGame();
    return 0;
}