#include "Player.h"
#include "Weapon.h"
#include "Bullet.h"
#include "CircleObject.h"

Player::Player(GameManager* game)
    : BoxObject(game), health(100), impulseStrength(5.0f), mass(4), dampening(0.99f) {
    pos.y = 0;
    initTexture("assets/spaceship.png");
    initSprite();
    sprite.setOrigin(height * 15, width * 15);  // Centers sprite over hit box
    sprite.scale(0.08f, 0.08f);                 // Makes sprite smaller
    this->dynamic = true;
}

// Functions govern player movement, using physics
void Player::update(float gametime) {
    // Dampen Movement
    velocity.x *= dampening;
    velocity.y *= dampening;

    pos.x += velocity.x * gametime;
    pos.y += velocity.y * gametime;
    shape.setPosition({pos.x - (width / 2), pos.y - (height / 2)});
    sprite.setPosition({pos.x - (width / 2), pos.y - (height / 2)});
}

void Player::applyImpulse(Vector2 impulse) {
    velocity.x += (impulse.x * impulseStrength) / mass;
    velocity.y += (impulse.y * impulseStrength) / mass;
}

void Player::shootWeapon() {
    // Creates bullet object if cooldown in weapon class is over
    if (currentWeapon.shootCooldownOver()) {
        switch (currentWeapon.getPowerup()) {
        // SINGLE, DOUBLE etc refers to the powerup being used when shooting
        // This can be refactored into a function after powerup ideas are sorted out
        case Weapon::SINGLE: {
            Bullet* bullet = new Bullet(game, {pos.x + 10, pos.y - 3}, 5, 15, 0, 1, sf::Color::White);
            game->objects.push_back(bullet);
            break;
        }
        case Weapon::DOUBLE: {
            Bullet* bullet = new Bullet(game, {pos.x + 10, pos.y - 3}, 5, 15, 0, 1, sf::Color::White);
            game->objects.push_back(bullet);
            Bullet* bullet2 = new Bullet(game, {pos.x + 30, pos.y - 3}, 5, 15, 0, 1, sf::Color::White);
            game->objects.push_back(bullet2);
            break;
        }
        case Weapon::TRIPLE: {
            // Triple powerup code
            break;
        }
        case Weapon::RICOCHET: {
            // Ricochet powerup code
            break;
        }
        }
    }
}