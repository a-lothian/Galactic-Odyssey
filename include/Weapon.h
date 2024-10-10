#ifndef WEAPON_H
#define WEAPON_H

#include "string"
#include <SFML/Graphics.hpp>

class Weapon {
   public:
    Weapon();
    ~Weapon();

    std::string name;
    int damage;
    bool shoot(); // Returns true if cooldown is over

   private:
    sf::Clock clock;
    sf::Time elapsed;
    float cooldown;

};
#endif