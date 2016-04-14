#include "Plant.h"

using namespace std;

Plant::Plant()
{

    max_calories  = 100;
    curr_calories = 25;

}

Plant::~Plant()
{

}

int Plant::get_max_calories()
{ return max_calories; }

void Plant::set_max_calories(int m)
{ max_calories = m; }


void Plant::eat(int x)
{ set_curr_calories(get_curr_calories() + x);}

void Plant::die(){}

void Plant::take_turn()
{
    if (get_curr_calories() < get_max_calories())
    {eat(1);}
}


