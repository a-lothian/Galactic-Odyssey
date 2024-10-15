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
class BoxObject;
class CircleObject;
class Bullet;

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
    std::vector<BasicEnemy*> enemies;
    std::vector<GameObject*> colliders;
    std::vector<Bullet*> bullets;

    // game variables
    int score;
    float scrollSpeed;
    float difficulty;

    // Game loop
    void toString();
    void HandleCollisions(float gametime, int substeps);
    void cullOutOfBounds();
    void updateGame();
    void renderGame();

    // Object creation, adds objects to objects and collisions if required
    BoxObject* createBox(float x, float y, float width, float height, sf::Color colour, bool doCollision = true, bool addToObjects = true);
    CircleObject* createCircle(float x, float y, float radius, sf::Color colour, bool doCollision = true, bool addToObjects = true);
    Bullet* createBullet(GameObject* parent, float x, float y, float radius, float speed, float angle, int damage, sf::Color colour, bool doCollision);

    // Enemy spawning
    BasicEnemy* createBasicEnemy_Single(float x, float y);
    // void createEnemy_3_Cluster(Vector2 pos);
    // void createEnemy_3_Line(Vector2 pos);

    void printObjectSize() { std::cout << "Objects size: " << objects.size() << std::endl; }

    // Saving and loading
    void saveGame();
    void loadSave();

    //  User interface
    sf::Text score_text;
    sf::Text timer_text;
    sf::Font roboto;
    int seconds;
    sf::Clock timer;

    // Barriers
    GameObject* barrierL;
    GameObject* barrierR;
    GameObject* barrierB;
    GameObject* barrierT;

    sf::Texture backgroundTexture;  // Background texture
    sf::Sprite backgroundSprite;    // Background sprite
    sf::Texture starTexture;        // Star texture
    sf::Sprite starSprite1;         // Star sprite
    sf::Sprite starSprite2;         // Second star sprite
    void initBackgroud();           // Initializes background
    void repeatStar();              // Repeats the star

    void initHUD();
    sf::Text createText(std::string str, int characterSize, sf::Color fillColour, sf::Vector2f position);
    void updateScore(int newScore);
    void updateTimer(int newSeconds);
};

#endif