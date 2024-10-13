#include <iostream>
#include "GameManager.h"
#include <SFML/Graphics.hpp>
#include "BoxObject.h"
#include "CircleObject.h"

#define X_RES 500
#define Y_RES 800

int main() {
    GameManager gameManager;
    BoxObject box(&gameManager, {250, 500}, 100, 100, sf::Color::Red);   // red box in middle of screen
    gameManager.createEnemy_Single(250, 100);
    box.initTexture("assets/enemy.png");
    box.initSprite();
    box.sprite.scale(0.75f, 0.75f);
    box.sprite.setOrigin(115, 110);
    CircleObject circle(&gameManager, {250, 300}, 50, sf::Color::Blue);  // blue circle in middle of screen
    gameManager.objects.push_back(&box);
    gameManager.objects.push_back(&circle);
    gameManager.runGame();
    return 0;
}