#ifndef DEER_H
#define DEER_H
#include "Herbivore.h"
#include <Living_Being.h>
#include <iostream>

#define TILE_SIZE 20

using namespace std;

class Deer : public Herbivore
{
 public:
    Deer();
    ~Deer();
};
#endif // DEER_H
