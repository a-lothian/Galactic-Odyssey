#include <iostream>
#include "GameManager.h"
#include <SFML/Graphics.hpp>
#include "BoxObject.h"
#include "CircleObject.h"
#include "Powerup.h"

#define X_RES 500
#define Y_RES 800

void printNewLines(int num) {
    for (int i = 0; i < num; i++) {
        std::cout << std::endl;
    }
}

int main() {
    printNewLines(50);
    std::cout << "Hello!\nWelcome to Galactic Odyssey!" << std::endl;
    std::cout << "Use the arrow keys to move and spacebar to shoot." << std::endl;
    printNewLines(3);
    std::cout << "Would you like to play? (y/n)" << std::endl;

    char answer;
    bool validInput = false;
    std::cin >> answer;

    while (!validInput) {
        if (answer == 'y' || answer == 'Y') {
            validInput = true;
            std::cout << "Great! Let's get started!" << std::endl;
        } else if (answer == 'n' || answer == 'N') {
            std::cout << "Okay, goodbye!" << std::endl;
            return 0;
        } else {
            std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
            std::cin >> answer;
        }
    }

    GameManager gameManager;
    gameManager.loadSave();  // testing
    gameManager.initHUD();   // testing
    gameManager.runGame();

    return 0;
}