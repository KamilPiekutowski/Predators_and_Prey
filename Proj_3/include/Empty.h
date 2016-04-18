#ifndef EMPTY_H
#define EMPTY_H
#include "Living_Being.h"
#include "Plant.h"


#include <iostream>

#define TILE_SIZE 20

using namespace std;


class Empty : public Plant
{
    public:
        Empty();
        ~Empty();
};
// GRASS_H

#endif // EMPTY_H
