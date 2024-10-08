#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "GameObject.h"
#include <iostream>
#include <vector>

class GameManager {
   public:
    GameManager();
    ~GameManager() {};

    void runGame();

    struct position {
        float x;
        float y;
    };

   private:
    sf::RenderWindow window;
    int framerate;
    float gamespeed;

    // game classes
    InputManager inputManager;
    GameObject* player;
    std::vector<GameObject*> enemies;

    // game variables
    int score;
    float scrollSpeed;

    // Game loop
    void updateGame();
    void renderGame();

    // Enemy spawning
    void createEnemy_Single(position pos);
    void createEnemy_3_Cluster(position pos);
    void createEnemy_3_Line(position pos);
};

#endif