#include "Rabbit.h"
#include "Square.h"
#include <iostream>
using namespace std;

Rabbit::Rabbit()
{
    set_move_made(false);
    set_max_age(25);
    set_curr_age(0);
    set_max_calories(45);
    set_curr_calories(10);
    set_metabolic_rate(3);
    set_calories_per_grass(5);
    set_calories_per_20_grass(1);
    set_calories_per_flower(6);
    set_calories_per_30_flowers(2);
    set_reproductive_rate(50);
    set_min_age_to_reproduce(10);
    set_min_calories_to_reproduce(40);
    set_min_calories_to_evade(30);
}

Rabbit::~Rabbit()
{
    //dtor
}

// inherited methods
void Rabbit::age()
{
    set_curr_age(get_curr_age()+1);
}
void Rabbit::evade(){}
void Rabbit::die(){}
void Rabbit::hunger()
{
    set_curr_calories(get_curr_calories() - get_metabolic_rate());
}
void Rabbit::move(){}
void Rabbit::reproduce(){}
void Rabbit::eat(int e)
{
    set_curr_calories(get_curr_calories() + e);
}
void Rabbit::take_turn(){}


// getters/setters

void Rabbit::set_move_made(bool b)
{
     move_made = b;
}

bool Rabbit::get_move_made()
{
     return move_made;
}
int Rabbit::get_max_age()
{ return max_age; }

void Rabbit::set_max_age(int ma)
{ max_age = ma; }

int Rabbit::get_curr_age()
{ return curr_age; }

void Rabbit::set_curr_age(int ca)
{ curr_age = ca; }

int Rabbit::get_max_calories()
{ return max_calories; }

void Rabbit::set_max_calories(int mc)
{ max_calories = mc; }

int Rabbit::get_curr_calories()
{ return curr_calories; }

void Rabbit::set_curr_calories(int cc)
{ curr_calories = cc; }

int Rabbit::get_metabolic_rate()
{ return metabolic_rate; }

void Rabbit::set_metabolic_rate(int mr)
{ metabolic_rate = mr; }

int Rabbit::get_calories_per_grass()
{ return calories_per_grass; }

void Rabbit::set_calories_per_grass(int cpg)
{ calories_per_grass = cpg; }

int Rabbit::get_calories_per_20_grass()
{ return calories_per_20_grass; }

void Rabbit::set_calories_per_20_grass(int cp20g)
{ calories_per_20_grass = cp20g; }

int Rabbit::get_calories_per_flower()
{ return calories_per_flower; }

void Rabbit::set_calories_per_flower(int cpf)
{ calories_per_flower = cpf; }

int Rabbit::get_calories_per_30_flowers()
{ return calories_per_30_flowers; }

void Rabbit::set_calories_per_30_flowers(int cp30f)
{ calories_per_30_flowers = cp30f; }

int Rabbit::get_reproductive_rate()
{ return reproductive_rate; }

void Rabbit::set_reproductive_rate(int rr)
{ reproductive_rate = rr; }

int Rabbit::get_min_age_to_reproduce()
{ return min_age_to_reproduce; }

void Rabbit::set_min_age_to_reproduce(int mar)
{ min_age_to_reproduce = mar; }

int Rabbit::get_min_calories_to_reproduce()
{ return min_calories_to_reproduce; }

void Rabbit::set_min_calories_to_reproduce(int mcr)
{ min_calories_to_reproduce = mcr; }

int Rabbit::get_min_calories_to_evade()
{ return min_calories_to_evade; }

void Rabbit::set_min_calories_to_evade(int mce)
{ min_calories_to_evade = mce; }

