#include "Weapon.h"
#include "BoxObject.h"

Weapon::Weapon(GameManager* game, GameObject* parent)
    : game(game), parent(parent) {
    if (game == nullptr) {
        std::cerr << "Error: GameManager is null! in weapon" << std::endl;
    }

    cooldown = 0.250;
    bulletsPerShot = 1;
    richochet = false;
}

Weapon::~Weapon() {}

bool Weapon::shootCooldownOver() {
    // Weapon cooldown logic

    elapsed = clock.getElapsedTime();
    if (elapsed.asSeconds() >= cooldown) {
        std::cout << "Shoot!" << std::endl;  // For testing
        clock.restart();
        return true;  // If cooldown is over, return true
    }

    return false;
}

void Weapon::shoot() {
    if (shootCooldownOver()) {
        game->createBullet(parent, parent->pos.x, parent->pos.y, 5, 15, 0, 1, sf::Color::White, false);
    }
}
