#ifndef PLANT_H
#define PLANT_H
#include "Living_Being.h"


class Plant : public Living_Being
{
private:
    int max_calories;
    int curr_calories;
    int amount_to_eat = 1;
    int plant_rate;


public:
    Plant();
    ~Plant();

    int get_max_calories();
    void set_max_calories(int c);
    void eat(int);
    void die();
    void take_turn();
    void set_plant_rate(int);
    int get_plant_rate();

};
#endif // PLANT_H
