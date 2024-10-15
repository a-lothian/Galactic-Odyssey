#include "Powerup.h"
#include "BoxObject.h"

Powerup::Powerup(GameManager* game, Vector2 pos) : BoxObject(game) {
    shape.setPosition({pos.x, pos.y});
}

void Powerup::update(float gametime) {
    pos.y = velocity.y * gametime;
    shape.setPosition({pos.x, pos.y});
}
 