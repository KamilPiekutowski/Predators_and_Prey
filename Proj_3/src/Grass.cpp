#include "Grass.h"
#include <iostream>

using namespace std;

Grass::Grass()
{
    max_calories  = 100;
    curr_calories = 20;
    identifier = 'G';
}

Grass::~Grass()
{

}

int Grass::get_max_calories()
{ return max_calories; }

void Grass::set_max_calories(int m)
{ max_calories = m; }

int Grass::get_curr_calories()
{ return curr_calories;}

void Grass::set_curr_calories(int c)
{ curr_calories = c;}

void Grass::eat(int x)
{ set_curr_calories(get_curr_calories() + x);}

void Grass::die(){}

void Grass::take_turn()
{
    if (get_curr_calories() < get_max_calories())
    {eat(1);}
}
