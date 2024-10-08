#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "InputManager.h"
#include "GameObject.h"
#include <iostream>
#include <vector>

class GameManager {
   public:
    GameManager();
    ~GameManager();

   private:
    InputManager inputManager;
    GameObject* player;
    std::vector<GameObject*> enemies;

    int score;

    void intializeGame();
    void updateGame();
    void renderGame();
    void runGame();  // contians the main game loop
};

#endif