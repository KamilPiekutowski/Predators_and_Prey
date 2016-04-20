#ifndef FLOWER_H
#define FLOWER_H
#include "Plant.h"
#include <iostream>
#define TILE_SIZE 20

using namespace std;

///////////// Plants //////////////////
class Flower : public Plant
{
    public:
        Flower();
        ~Flower();

};
#endif // FLOWER_H
