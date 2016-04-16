#ifndef FACTORY_H
#define FACTORY_H
#include "Living_Being.h"
#include "Grass.h"
#include "Flower.h"
#include "Rabbit.h"
#include "Deer.h"

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
            /*
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
            */
        }
    }
};

#endif // FACTORY_H