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

    struct Position {
        float x;
        float y;
    };

    sf::RenderWindow window;  // must be public as objects aren't children of GameManager

   public:  // changed to test rendering in main.cpp, will be private later
    // window
    sf::Event event;  // to be passed to input manager (keystroke inputs)
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
    void checkCollisions();
    void updateGame();
    void renderGame();

    // Enemy spawning
    void createEnemy_Single(float x, float y);
    void createEnemy_3_Cluster(Position pos);
    void createEnemy_3_Line(Position pos);
};

#endif