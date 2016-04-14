#ifndef FLOWER_H
#define FLOWER_H
#include "Living_Being.h"

///////////// Plants //////////////////
class Flower : public Living_Being
{
private:
    int max_calories;
    int curr_calories;
    int amount_to_eat = 1;
    char identifier;

public:
    Flower();
    ~Flower();

    void set_curr_calories(int c);
    int get_curr_calories();
    int get_max_calories();
    void set_max_calories(int c);
    void remove_calories(int c);
    void eat(int);
    void die();
    void take_turn();
};
#endif // FLOWER_H
