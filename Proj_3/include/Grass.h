#ifndef GRASS_H
#define GRASS_H
#include "Living_Being.h"
#include "Plant.h"

#include <iostream>

#define TILE_SIZE 20

using namespace std;


class Grass : public Plant
{
    public:
        Grass();
        ~Grass();
};
#endif // GRASS_H
