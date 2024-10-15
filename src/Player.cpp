#include "Player.h"
#include "Weapon.h"
#include "Bullet.h"
#include "CircleObject.h"

Player::Player(GameManager* game)
    : BoxObject(game), health(5), impulseStrength(5.0f), mass(4), dampening(0.99f) {
    if (game == nullptr) {
        std::cerr << "Error: GameManager is null in Player!" << std::endl;
    }

    this->currentWeapon = new Weapon(game, this);

    pos = {250, 700};
    this->isPhysics = true;
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
    currentWeapon->shoot();
}