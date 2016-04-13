#ifndef GRASS_H
#define GRASS_H
#include "Living_Being.h"

///////////// Plants //////////////////
class Grass : public Living_Being
{
private:
    int max_calories;
    int curr_calories;
    int amount_to_eat = 1;
    char identifier;

public:
    Grass();
    ~Grass();
    using Living_Being::Living_Being;



    void set_curr_calories(int c);
    int get_curr_calories();
    int get_max_calories();
    void set_max_calories(int c);
    void eat(int);
    void die();
    void take_turn();

};
#endif // GRASS_H
