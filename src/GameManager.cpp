#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Player.h"
#include "BasicEnemy.h"
#include "Weapon.h"
#include "BoxObject.h"
#include "CircleObject.h"
#include "Bullet.h"
#include <fstream>
#include <string>

GameManager::GameManager()
    : window(sf::VideoMode(500, 800), "Galactic Odyssey", sf::Style::Titlebar | sf::Style::Close) {
    window.setKeyRepeatEnabled(true);
    player = new Player(this);
    objects.push_back(player);
    inputManager = new InputManager(player);

    // create test objects
    BoxObject* barrierL = createBox(565, 400, 100, 1000, sf::Color::Red, true);
    BoxObject* barrierR = createBox(-65, 400, 100, 1000, sf::Color::Red, true);

    barrierL->dynamic = true;
    barrierR->dynamic = true;

    initBackgroud();
}

void GameManager::initBackgroud() {
    if (!this->backgroundTexture.loadFromFile("assets/background.jpg")) {
        std::cout << "Error loading background file." << std::endl;
    }
    if (!this->starTexture.loadFromFile("assets/background_star.jpg"))  {
        std::cout << "Error loading star file." << std::endl;
    }
    this->backgroundSprite.setTexture(this->backgroundTexture);
    this->backgroundSprite.setPosition(-700, -475);

    this->starTexture.setRepeated(true);
    this->starSprite1.setTexture(this->starTexture);
    this->starSprite2.setTexture(this->starTexture);
    this->starSprite1.setPosition(-700, -445 - this->backgroundSprite.getGlobalBounds().height);
    this->starSprite2.setPosition(-700, -445 - this->starSprite1.getGlobalBounds().height - 1285);
}

void GameManager::repeatStar()  {
    if (this->starSprite1.getPosition().y >= this->window.getSize().y) {
        this->starSprite1.setPosition(-700, -445 - this->starSprite1.getGlobalBounds().height);
    }

    if (this->starSprite2.getPosition().y >= this->window.getSize().y) {
        this->starSprite2.setPosition(-700, -445 - this->starSprite2.getGlobalBounds().height);
    }
}

void GameManager::toString() {
    for (GameObject* object : objects) {
        std::cout << object->toString() << std::endl;
    }
}

void GameManager::renderGame() {
    this->window.clear();
    this->window.draw(this->backgroundSprite);
    this->window.draw(this->starSprite1);
    this->window.draw(this->starSprite2);

    for (GameObject* object : objects) {
        if (object->render) {
            object->drawObject();
        }
    }
    for (BasicEnemy* enemy : enemies) {
        enemy->drawObject();
    }

    this->window.draw(score_text);

    this->window.display();
    this->backgroundSprite.move(0, 20);
    this->starSprite1.move(0, 20);
    this->starSprite2.move(0, 20);
    repeatStar();
}

BoxObject* GameManager::createBox(float x, float y, float width, float height, sf::Color colour, bool doCollision) {
    BoxObject* box = new BoxObject(this, {x, y}, width, height, colour);

    objects.push_back(box);

    if (doCollision) {
        colliders.push_back(box);
    }
    return box;
}

CircleObject* GameManager::createCircle(float x, float y, float radius, sf::Color colour, bool doCollision) {
    CircleObject* circle = new CircleObject(this, {x, y}, radius, colour);

    objects.push_back(circle);

    if (doCollision) {
        colliders.push_back(circle);
    }
    return circle;
}

BasicEnemy* GameManager::createBasicEnemy_Single(float x, float y) {
    BasicEnemy* enemy = new BasicEnemy(this, {x, y});
    enemies.push_back(enemy);
    return enemy;
}

void GameManager::runGame() {
    framerate = 60;
    gamespeed = 1 / framerate;
    window.setFramerateLimit(framerate);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                saveGame();
                window.close();
            }
        }

        // Update and render game
        updateGame();
        renderGame();
    }
}

void GameManager::initHUD() {
    std::string score_check = "Score: ";
    score_check.append(std::to_string(score));
    score_text = createText(score_check, 25, sf::Color::White, {350, 20});
}

sf::Text GameManager::createText(std::string str, int characterSize, sf::Color fillColour, sf::Vector2f position) {
    // Creates text
    sf::Text text;
    if (!roboto.loadFromFile("fonts/Roboto-Light.ttf"))  // Should eventually find a better font than this
    {
        std::cerr << "Failed to load font. Fonts directory may be missing, or file is inaccessible." << std::endl;
    }
    text.setFont(roboto);
    text.setString(str);
    text.setCharacterSize(characterSize);
    text.setFillColor(fillColour);
    text.setPosition(position);
    return text;
}

void GameManager::updateScore(int newScore) {
    score = newScore;
    std::string score_check = "Score: ";
    score_check.append(std::to_string(score));
    score_text.setString(score_check);
}

Bullet* GameManager::createBullet(GameObject* parent, float x, float y, float radius, float speed, float angle, int damage, sf::Color colour, bool doCollision) {
    Bullet* bullet = new Bullet(this, parent, {parent->pos.x, parent->pos.y}, radius, speed, angle, damage, colour);

    objects.push_back(bullet);

    if (doCollision) {
        colliders.push_back(bullet);
    }
    return bullet;
}

void GameManager::saveGame() {
    std::ofstream user_save;
    user_save.open("saves/user_save");
    if (!user_save.is_open()) {
        std::cerr << "The saves directory could not be accessed. Game failed to save. \n";
    } else {
        // Will store the name of the player (assuming we ask for name at the start) and their score
        user_save << "score=" << score << std::endl;
        // user_save << "name=" << name << std::endl;
        user_save.close();
    }
}

void GameManager::loadSave() {
    std::ifstream user_load;
    user_load.open("saves/user_save");
    if (!user_load.is_open()) {
        std::cout << "No save detected. \n";
        score = 0;  // If there is no save, sets score to 0
    } else {
        // Loads player score
        std::string score_str;
        user_load >> score_str;
        if (score_str.substr(0,6) != "score=") {
            // If the save file is not formatted correctly, resets save.
            std::cerr << "Save loading error, score not set correctly. \n";
            score = 0;
            user_load.close();
            return;
        }
        score_str = score_str.substr(6);  // Removing the "score=" part from the line
        score = std::stoi(score_str);
        user_load.close();
    }
}

void GameManager::HandleCollisions(float gametime, int substeps) {
    float sub_dt = gametime / substeps;

    for (int s = 0; s < substeps; s++) {
        for (u_long i = 0; i < objects.size(); i++) {
            objects[i]->update(sub_dt);
        }

        for (u_long i = 0; i < objects.size(); i++) {
            for (u_long j = i + 1; j < objects.size(); j++) {
                bool isColliding = objects[i]->isColliding(objects[j]);
                if (isColliding && objects[i]->isPhysics && objects[j]->isPhysics) {
                    objects[i]->resolveCollision(objects[j]);
                }
            }
        }
    }
}

void GameManager::updateGame() {
    /*
        General approach:
        1. Check inputs
        2. Do events (spawning stuff, AI logic, ect)
        3. Simulate objects (movement, collisions, ect)
    */
    //  Handle input
    inputManager->CheckInputs();

    // Do events

    player->applyImpulse(inputManager->Direction);  // Move player

    if (inputManager->space) {
        player->shootWeapon();
    }

    for (u_long i = 0; i < objects.size(); i++) {  // simulate all objects 1 frame
    }

    // Check collisions + resolve collisions

    HandleCollisions(1, 8);  // 1 frame of collision resolution with 8 substeps
}
