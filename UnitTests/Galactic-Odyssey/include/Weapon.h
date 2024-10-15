#ifndef WEAPON_H
#define WEAPON_H

#include "string"
#include <SFML/Graphics.hpp>

#include "GameManager.h"

class Weapon {
   public:
    Weapon(GameManager* game, GameObject* parent);
    ~Weapon();

    GameManager* game;
    GameObject* parent;

    std::string name;
    int damage;
    float cooldown;
    bool shootCooldownOver();  // Returns true if cooldown is over
    void shoot();

    int bulletsPerShot;
    bool richochet;

   private:
    sf::Clock clock;
    sf::Time elapsed;
};
#endif