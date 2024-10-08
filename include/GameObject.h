#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include <vector>

class GameObject {
   public:
    struct Position {
        int x;
        int y;
    };

    Position pos;

    GameObject();
    ~GameObject();

   private:
};

#endif