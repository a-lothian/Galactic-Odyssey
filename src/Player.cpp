#include "Player.h"
#include "Weapon.h"
#include "Bullet.h"
#include "CircleObject.h"

Player::Player(GameManager* game)
    : BoxObject(game), health(100), impulseStrength(2.5f), mass(2), dampening(0.9f) {
    pos.y = 0;
}

// Functions govern player movement, using physics
void Player::update(float gametime) {
    // Dampen Movement
    velocity.x *= dampening;
    velocity.y *= dampening;

    pos.x += velocity.x * gametime;
    pos.y += velocity.y * gametime;
    shape.setPosition({pos.x, pos.y});
}

void Player::applyImpulse(Vector2 impulse) {
    velocity.x += (impulse.x * impulseStrength) / mass;
    velocity.y += (impulse.y * impulseStrength) / mass;
}

void Player::shootWeapon() {
    // Creates bullet object if cooldown in weapon class is over
    if (currentWeapon.shoot()) {
        Bullet* bullet = new Bullet(game, {pos.x + 10, pos.y - 3}, 5, 15, 0, 1, sf::Color::White);
        game->objects.push_back(bullet);
    }
}