#ifndef FACTORY_H
#define FACTORY_H
#include "Living_Being.h"
#include "Grass.h"
#include "Flower.h"
#include "Rabbit.h"
#include "Deer.h"
#include "Wolf.h"
#include "Bear.h"
#include "Empty.h"

class Factory
{
public:
    static Living_Being* create_being(char id)
    {
        switch(id)
        {
            case('G'):
            {
                Living_Being* grass = new Grass();
                return grass;
            }
            case('F'):
            {
                Living_Being* flower = new Flower();
                return flower;
            }
            case('R'):
            {
                Living_Being* rabbit = new Rabbit();
                return rabbit;
            }
            case('D'):
            {
                Living_Being* deer = new Deer();
                return deer;
            }
            case('W'):
            {
                Living_Being* wolf = new Wolf();
                return wolf;
            }
            case('B'):
            {
                Living_Being* bear = new Bear();
                return bear;
            }
            case('P'):
                Living_Being* empty = new Empty();
                return empty;
        }
    }
};

#endif // FACTORY_H
