#include "BasicEnemy.h"
#include <cstdlib>
#include <ctime>

BasicEnemy::BasicEnemy(GameManager* game, Vector2 pos, int health, float speed, float weaponCooldown)
    : BoxObject(game, pos, 5, 5, sf::Color::Blue), health(health), speed(speed), pos(pos) {
    currentWeapon = new Weapon(game, this);
    currentWeapon->cooldown = weaponCooldown;

    toDelete = false;

    initTexture("assets/enemy1.png");
    initSprite();
    sprite.scale(0.2f, 0.2f);
    sprite.setOrigin(190, 100);
    shape.setPosition({pos.x, pos.y});
    sprite.setPosition({pos.x, pos.y});
}

BasicEnemy::~BasicEnemy() {
    std::srand(static_cast<unsigned>(std::time(0)));
    int randomIndex = std::rand() % 4;
    if (randomIndex == 3) {
        game->createPowerup(pos.x, pos.y);
    }
}

void BasicEnemy::update(float gametime) {
    pos.y += speed * gametime;

    shape.setPosition({pos.x, pos.y});
    sprite.setPosition({pos.x, pos.y});
}
