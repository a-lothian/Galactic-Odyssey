#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include <iostream>
#include <vector>

class GameObject;  // forward declaration, as GameObject needs to reference from GameManager (avoids circular dependency)

class GameManager {
   public:
    GameManager();
    ~GameManager() {};

    void runGame();  // main game loop

    struct Position {
        float x;
        float y;
    };

   protected:
    // window
    sf::RenderWindow window;
    sf::Event event;  // to be passed to input manager (keystroke inputs)
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
    void createEnemy_Single(float x, float y);
    void createEnemy_3_Cluster(Position pos);
    void createEnemy_3_Line(Position pos);
};

#endif