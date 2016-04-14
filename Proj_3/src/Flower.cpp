#include "Flower.h"
#include <iostream>
using namespace std;


Flower::Flower()
{
    max_calories  = 100;
    curr_calories = 25;
    identifier = 'F';
}

Flower::~Flower()
{

}

int Flower::get_max_calories()
{ return max_calories; }

void Flower::set_max_calories(int m)
{ max_calories = m; }

int Flower::get_curr_calories()
{ return curr_calories;}

void Flower::set_curr_calories(int c)
{ curr_calories = c;}

void Flower::eat(int x)
{ set_curr_calories(get_curr_calories() + x);}

void Flower::die(){}

void Flower::take_turn()
{
    if (get_curr_calories() < get_max_calories())
    {eat(0);}
}

void Flower::remove_calories(int c)
{
    curr_calories = get_curr_calories() - c;
}
