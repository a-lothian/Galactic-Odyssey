#include "Powerup.h"
#include "BoxObject.h"

Powerup::Powerup(GameManager* game, Vector2 pos) : BoxObject(game), pos(pos) {
    initTexture("assets/powerup.png");
    initSprite();
    sprite.scale(1.5f, 1.5f);
    sprite.setOrigin(0, 0);;
    shape.setPosition({pos.x, pos.y});
    sprite.setPosition({pos.x, pos.y});
    speed = 3;
}

void Powerup::update(float gametime) {
    pos.y += speed * gametime;
    shape.setPosition({pos.x, pos.y});
    sprite.setPosition({pos.x, pos.y});
}
 