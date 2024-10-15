#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "GameManager.h"
#include "InputManager.h"
#include "EnemyManager.h"

#include "GameObject.h"
#include "Player.h"
#include "BasicEnemy.h"
#include "Weapon.h"
#include "BoxObject.h"
#include "CircleObject.h"
#include "Bullet.h"
#include "Powerup.h"
#include <fstream>
#include <string>

GameManager::GameManager()
    : window(sf::VideoMode(500, 800), "Galactic Odyssey", sf::Style::Titlebar | sf::Style::Close) {
    window.setKeyRepeatEnabled(true);
    player = new Player(this);
    objects.push_back(player);
    inputManager = new InputManager(player);
    enemyManager = new EnemyManager(this);

    // create test objects
    BoxObject* barrierL = createBox(565, 400, 100, 100000, sf::Color::Red, true, false);
    BoxObject* barrierR = createBox(-65, 400, 100, 100000, sf::Color::Red, true, false);

    // Top + Bottom barriers shouldn't collide with bullets, enemies
    BoxObject* barrierB = createBox(250, 865, 500, 100, sf::Color::Green, false, false);
    BoxObject* barrierT = createBox(250, -65, 500, 100, sf::Color::Green, false, false);

    barrierL->dynamic = true;
    barrierR->dynamic = true;
    barrierB->dynamic = true;

    initBackgroud();
}

void GameManager::initBackgroud() {
    if (!this->backgroundTexture.loadFromFile("assets/background.jpg")) {
        std::cout << "Error loading background file." << std::endl;
    }
    if (!this->starTexture.loadFromFile("assets/background_star.jpg")) {
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

void GameManager::repeatStar() {
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
        object->drawObject();
    }
    for (Bullet* bullet : bullets) {
        bullet->drawObject();
    }
    for (BasicEnemy* enemy : enemies) {
        enemy->drawObject();
    }
    for (Powerup* powerup : powerups) {
        powerup->drawObject();
    }

    this->window.draw(score_text);
    this->window.draw(timer_text);

    this->window.display();
    this->backgroundSprite.move(0, 1 + (10 * difficulty));
    this->starSprite1.move(0, 1 + (10 * difficulty));
    this->starSprite2.move(0, 1 + (10 * difficulty));
    repeatStar();
}

BoxObject* GameManager::createBox(float x, float y, float width, float height, sf::Color colour, bool doCollision, bool addToObjects) {
    BoxObject* box = new BoxObject(this, {x, y}, width, height, colour);

    objects.push_back(box);

    if (doCollision) {
        colliders.push_back(box);
    }
    return box;
}

CircleObject* GameManager::createCircle(float x, float y, float radius, sf::Color colour, bool doCollision, bool addToObjects) {
    CircleObject* circle = new CircleObject(this, {x, y}, radius, colour);

    objects.push_back(circle);

    if (doCollision) {
        colliders.push_back(circle);
    }
    return circle;
}

BasicEnemy* GameManager::createBasicEnemy_Single(float x, float y, int health, float speed, float weaponCooldown) {
    BasicEnemy* enemy = new BasicEnemy(this, {x, y}, health, speed, weaponCooldown);
    enemies.push_back(enemy);
    return enemy;
}

Powerup* GameManager::createPowerup(float x, float y) {
    std::srand(static_cast<unsigned>(std::time(0)));
    int randomIndex = std::rand() % 3;
    Powerup* powerup = new Powerup(this, static_cast<Powerup::powerupType>(randomIndex), {x, y});
    powerups.push_back(powerup);
    return powerup;
}

void GameManager::runGame() {
    framerate = 60;
    gamespeed = 1 / framerate;
    seconds = 0;
    window.setFramerateLimit(framerate);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                saveGame();
                window.close();
            }
        }

        // Updates the timer in seconds
        if (timer.getElapsedTime().asSeconds() >= 1) {
            timer.restart();
            seconds++;
            updateTimer(seconds);
        }

        difficulty = (float)seconds / 20;

        // Update and render game

        updateGame();
        renderGame();

        if (player->health < 1) {
            window.close();
        }
    }
}

void GameManager::initHUD() {
    seconds = 0;
    std::string ui_score = "Score: ";
    std::string ui_timer = "Time: ";
    ui_score.append(std::to_string(score));
    score_text = createText(ui_score, 25, sf::Color::White, {30, 20});
    timer_text = createText(ui_timer, 25, sf::Color::White, {340, 20});
    updateTimer(seconds);
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
    text.setOutlineThickness(4.0f);
    text.setOutlineColor(sf::Color::Black);
    return text;
}

void GameManager::updateScore(int newScore) {
    score = newScore;
    std::string score_check = "Score: ";
    score_check.append(std::to_string(score));
    score_text.setString(score_check);
}

void GameManager::updateTimer(int newSeconds) {
    seconds = newSeconds;
    int minutes = seconds / 60;
    int remainingSeconds = seconds % 60;

    // Formatting the time
    std::string time_check = "Time: ";
    if (seconds < 600) {
        time_check.append("0");
    }
    time_check.append(std::to_string(minutes));
    time_check.append(":");
    if (remainingSeconds < 10) {
        time_check.append("0");
    }
    time_check.append(std::to_string(remainingSeconds));

    timer_text.setString(time_check);
}

Bullet* GameManager::createBullet(GameObject* parent, float x, float y, float radius, float speed, float angle, int damage, sf::Color colour, bool doCollision) {
    Bullet* bullet = new Bullet(this, parent, {parent->pos.x, parent->pos.y}, radius, speed, angle, damage, colour);

    bullets.push_back(bullet);
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
        if (score_str.substr(0, 6) != "score=") {
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
        // Update objects
        for (GameObject* obj : objects) {
            obj->update(sub_dt);
        }
        for (Bullet* bullet : bullets) {
            bullet->update(sub_dt);
        }
        for (BasicEnemy* enemy : enemies) {
            enemy->update(sub_dt);
        }

        // Handle collisions between objects
        for (u_long i = 0; i < objects.size(); i++) {
            for (u_long j = i + 1; j < objects.size(); j++) {
                bool isColliding = objects[i]->isColliding(objects[j]);
                if (isColliding && objects[i]->isPhysics && objects[j]->isPhysics) {
                    objects[i]->resolveCollision(objects[j]);
                }
            }
        }

        for (u_long i = 0; i < powerups.size(); i++) {
            bool isColliding = powerups[i]->pos.distance(player->pos) < 70;
            if (isColliding) {
                switch (powerups[i]->power) {
                case Powerup::powerupType::ADDBULLET: {
                    player->currentWeapon->bulletsPerShot += 1;
                    break;
                }
                case Powerup::powerupType::FIRERATE: {
                    player->currentWeapon->cooldown *= 0.8f;
                    break;
                }
                case Powerup::powerupType::DAMAGE: {
                    player->currentWeapon->damage += 1;
                    break;
                }
                }
                delete powerups[i];
                powerups.erase(powerups.begin() + i);
                i--;
            }
        }

        for (u_long i = 0; i < enemies.size(); i++) {
            if (enemies[i]->pos.y > 810) {
                player->health -= 1;
                enemies[i]->toDelete = true;
            }
        }

        // Handle collisions between bullets and enemies
        for (Bullet* check_bullet : bullets) {
            if (check_bullet->toDelete)
                continue;  // Skip if already marked for deletion

            for (BasicEnemy* check_enemy : enemies) {
                if (check_enemy->toDelete)
                    continue;  // Skip if already marked for deletion

                bool isBulletColliding = check_bullet->pos.distance(check_enemy->pos) < 70;

                if (isBulletColliding) {
                    // Reduce enemy health
                    check_enemy->health -= check_bullet->damage;
                    std::cout << "enemy health: " << check_enemy->health << std::endl;

                    // Mark bullet for deletion
                    check_bullet->toDelete = true;

                    // Mark enemy for deletion if health is zero or less
                    if (check_enemy->health <= 0) {
                        check_enemy->toDelete = true;
                    }

                    break;  // Exit the enemies loop for this bullet
                }
            }
        }

        // Remove bullets marked for deletion
        bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                                     [](Bullet* b) {
                                         if (b->toDelete) {
                                             delete b;
                                             return true;
                                         }
                                         return false;
                                     }),
                      bullets.end());

        // Remove enemies marked for deletion
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                                     [](BasicEnemy* e) {
                                         if (e->toDelete) {
                                             delete e;
                                             return true;
                                         }
                                         return false;
                                     }),
                      enemies.end());
    }
}

void GameManager::cullOutOfBounds() {
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i]->isWithinBounds(500, 800)) {
            delete objects[i];
            objects.erase(objects.begin() + i);
            i--;
        }
    }
    for (int i = 0; i < bullets.size(); i++) {
        if (bullets[i]->isWithinBounds(500, 800)) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
            i--;
        }
    }
}

void GameManager::updateGame() {
    /*
        General approach:
        1. Check inputs
        2. Do events (spawning stuff, AI logic, ect)
        3. Simulate objects (movement, collisions, ect)
        4. Cull objects outside window
    */
    //  Handle input
    inputManager->CheckInputs();

    // Do events

    player->applyImpulse(inputManager->Direction);  // Move player
    enemyManager->spawnEnemies();

    if (inputManager->space) {
        player->shootWeapon();
    }

    HandleCollisions(1, 8);  // 1 frame of collision resolution with 8 substeps

    cullOutOfBounds();  // remove objects that are out of bounds
}
