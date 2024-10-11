#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include <iostream>
#include <vector>

#define X_RES 500
#define Y_RES 800

class GameObject;  // forward declaration, as GameObject needs to reference from GameManager (avoids circular dependency)
class Player;

class GameManager {
   public:
    GameManager();
    ~GameManager() {};

    void runGame();  // main game loop

    sf::RenderWindow window;  // must be public as objects aren't children of GameManager

   public:  // changed to test rendering in main.cpp, will be private later
    // window
    int framerate;
    float gamespeed;

    // game classes
    Player* player;
    InputManager* inputManager;
    std::vector<GameObject*> objects;

    // game variables
    int score;
    float scrollSpeed;
    float difficulty;

    // Game loop
    void toString();
    void HandleCollisions(float gametime, int substeps);
    void updateGame();
    void renderGame();

    // Enemy spawning
    void createEnemy_Single(float x, float y);
    void createEnemy_3_Cluster(Vector2 pos);
    void createEnemy_3_Line(Vector2 pos);
};

#endif