#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include <vector>

class GameObject {
   public:
    GameObject();
    ~GameObject();

   private:
    std::vector<GameObject*> children;
};

#endif