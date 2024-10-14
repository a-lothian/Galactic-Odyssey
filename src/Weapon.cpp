#include "Weapon.h"
#include "BoxObject.h"

Weapon::Weapon(GameManager* game, GameObject* parent)
    : game(game), parent(parent) {
    if (game == nullptr) {
        std::cerr << "Error: GameManager is null! in weapon" << std::endl;
    }

    cooldown = 0.250;
    bulletsPerShot = 30;
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
        float coneSize = std::min((bulletsPerShot - 1) * 10, 100);
        float angleStep = coneSize / (bulletsPerShot - 1);  // The angle difference between each bullet
        float startAngle = 90 - (coneSize / 2);             // Start at -90 degrees (left side) for symmetry

        for (int i = 0; i < bulletsPerShot; i++) {
            float angle = startAngle + (i * angleStep);  // Calculate each bullet's angle
            game->createBullet(parent, parent->pos.x, parent->pos.y, 5, 15, angle, 1, sf::Color::White, false);
        }
    }
}
