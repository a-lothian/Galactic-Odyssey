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
class BasicEnemy;

class GameManager {
   public:
    GameManager();
    ~GameManager() {};

    void runGame();  // main game loop

    sf::RenderWindow window;  // must be public as objects aren't children of GameManager

   public:  // changed to test rendering in main.cpp, will be private later
    // window
    sf::Event event;  // to be passed to input manager (keystroke inputs)
    int framerate;
    float gamespeed;

    sf::Texture backgroundTexture;  // Background texture
    sf::Sprite backgroundSprite;  // Background sprite
    void initBackgroud();  // Initializes background

    // game classes
    Player* player;
    InputManager* inputManager;
    std::vector<GameObject*> objects;
    BasicEnemy* enemy;

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

    // Saving and loading
    void saveGame();
    void loadSave();
};

#endif