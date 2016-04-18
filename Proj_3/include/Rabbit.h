#ifndef RABBIT_H
#define RABBIT_H
#include "Herbivore.h"
#include <Living_Being.h>
#include <iostream>

#define TILE_SIZE 20

using namespace std;


class Rabbit : public Herbivore
{
 public:
    Rabbit();
    ~Rabbit();
};


#endif // RABBIT_H
