#include "Powerup.h"
#include "BoxObject.h"

Powerup::Powerup(GameManager* game, powerupType power, Vector2 pos) : BoxObject(game), power(power), pos(pos) {
    
    switch (power) { 
        case ADDBULLET: {
            initTexture("assets/powerup.png");
            break;
        }
        case FIRERATE: {
            initTexture("assets/lowercooldown.png");
            break;
        }
        case RICOCHET: {
            initTexture("assets/ricochet.png");
            break;
        }
    }

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
 