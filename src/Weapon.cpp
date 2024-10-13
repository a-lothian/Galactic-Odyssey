#include "Weapon.h"
#include "BoxObject.h"

Weapon::Weapon() {
    cooldown = 0.125f; 
    powerup = SINGLE;
}

Weapon::~Weapon() {}

bool Weapon::shootCooldownOver() {

    // Weapon cooldown logic

    elapsed = clock.getElapsedTime();
    if (elapsed.asSeconds() >= cooldown) {
        std::cout << "Shoot!" << std::endl; // For testing
        clock.restart();
        return true; // If cooldown is over, return true
    }

    return false;
}

Weapon::weaponType Weapon::getPowerup() {
    return powerup;
}

void Weapon::setPowerup(Weapon::weaponType newPowerup) {
    powerup = newPowerup;
}

