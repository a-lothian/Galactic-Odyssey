#include <iostream>
#include "GameManager.h"
#include <SFML/Graphics.hpp>
#include "BoxObject.h"
#include "CircleObject.h"

#define X_RES 500
#define Y_RES 800

int main() {
    GameManager gameManager;
    gameManager.loadSave(); // testing
    gameManager.initHUD(); // testing
    gameManager.createPowerup(50, 0); // testing
    gameManager.runGame();


    return 0;
}