#include "Weapon.h"
#include "BoxObject.h"

Weapon::Weapon() {
    cooldown = 0.125f; 
}

Weapon::~Weapon() {}

bool Weapon::shoot() {

    // Weapon cooldown logic

    elapsed = clock.getElapsedTime();
    if (elapsed.asSeconds() >= cooldown) {
        std::cout << "Shoot!" << std::endl; // For testing
        clock.restart();
        return true; // If cooldown is over, return true
    }

    return false;
}
