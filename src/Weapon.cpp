#include "Weapon.h"
#include "BoxObject.h"

Weapon::Weapon(GameManager* game, GameObject* parent)
    : game(game), parent(parent) {
    if (game == nullptr) {
        std::cerr << "Error: GameManager is null! in weapon" << std::endl;
    }

    cooldown = 0.5;
    bulletsPerShot = 1;
    richochet = false;
    damage = 1;
}

bool Weapon::shootCooldownOver() {
    // Weapon cooldown logic

    elapsed = clock.getElapsedTime();
    if (elapsed.asSeconds() >= cooldown) {
        clock.restart();
        return true;  // If cooldown is over, return true
    }

    return false;
}

void Weapon::shoot() {
    if (shootCooldownOver()) {
        if (bulletsPerShot == 1) {
            game->createBullet(parent, parent->pos.x, parent->pos.y, 5, 15, 90, damage, sf::Color::White, false);
        } else {
            float coneSize = std::min((bulletsPerShot - 1) * 10, 100);
            float angleStep = coneSize / (bulletsPerShot - 1);  // The angle difference between each bullet
            float startAngle = 90 - (coneSize / 2);             // Start at -90 degrees (left side) for symmetry

            for (int i = 0; i < bulletsPerShot; i++) {
                float angle = startAngle + (i * angleStep);  // Calculate each bullet's angle
                game->createBullet(parent, parent->pos.x, parent->pos.y, 5, 15, angle, damage, sf::Color::White, false);
            }
        }
    }
}
