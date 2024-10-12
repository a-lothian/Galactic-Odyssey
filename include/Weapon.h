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
    bool shootCooldownOver(); // Returns true if cooldown is over

    enum weaponType { // General powerup ideas
        SINGLE,
        DOUBLE,
        TRIPLE,
        RICOCHET
    };

    weaponType getPowerup();

    void setPowerup(Weapon::weaponType newPowerup);

   private:
    sf::Clock clock;
    sf::Time elapsed;
    float cooldown;

    enum weaponType powerup;
    


};
#endif