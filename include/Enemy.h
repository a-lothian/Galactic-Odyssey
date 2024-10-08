#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"

class Enemy : public GameObject {
   public:
    Enemy();
    ~Enemy();

    int health;
};
#endif