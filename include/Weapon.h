#ifndef WEAPON_H
#define WEAPON_H

#include "GameObject.h"
#include "string"

class Weapon : public GameObject {
   public:
    Weapon();
    ~Weapon();

    std::string name;
    int damage;
    float fireRate;

   private:
    float cooldown;

    void shoot();
};
#endif