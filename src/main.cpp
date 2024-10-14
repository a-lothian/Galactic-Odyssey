#include <iostream>
#include "GameManager.h"
#include <SFML/Graphics.hpp>
#include "BoxObject.h"
#include "CircleObject.h"

#define X_RES 500
#define Y_RES 800

int main() {
    GameManager gameManager;
    gameManager.runGame();
    return 0;
}