#include "Herbivore.h"
#include "Square.h"
#include <iostream>
using namespace std;

Herbivore::Herbivore()
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

Herbivore::~Herbivore()
{
    //dtor
}

// inherited methods
void Herbivore::age()
{
    set_curr_age(get_curr_age()+1);
}
void Herbivore::evade(){}
void Herbivore::die(){}
void Herbivore::hunger()
{
    set_curr_calories(get_curr_calories() - get_metabolic_rate());
    if(get_curr_calories() < 0) {
        set_curr_calories(0);
    }
}
void Herbivore::move(){}
void Herbivore::reproduce(){}
void Herbivore::eat(int e)
{
    set_curr_calories(get_curr_calories() + e);
}
void Herbivore::take_turn(){}


// getters/setters

void Herbivore::set_move_made(bool b)
{
     move_made = b;
}

bool Herbivore::get_move_made()
{
     return move_made;
}
int Herbivore::get_max_age()
{ return max_age; }

void Herbivore::set_max_age(int ma)
{ max_age = ma; }

int Herbivore::get_curr_age()
{ return curr_age; }

void Herbivore::set_curr_age(int ca)
{ curr_age = ca; }

int Herbivore::get_max_calories()
{ return max_calories; }

void Herbivore::set_max_calories(int mc)
{ max_calories = mc; }

int Herbivore::get_curr_calories()
{ return curr_calories; }

void Herbivore::set_curr_calories(int cc)
{ curr_calories = cc; }

int Herbivore::get_metabolic_rate()
{ return metabolic_rate; }

void Herbivore::set_metabolic_rate(int mr)
{ metabolic_rate = mr; }

int Herbivore::get_calories_per_grass()
{ return calories_per_grass; }

void Herbivore::set_calories_per_grass(int cpg)
{ calories_per_grass = cpg; }

int Herbivore::get_calories_per_20_grass()
{ return calories_per_20_grass; }

void Herbivore::set_calories_per_20_grass(int cp20g)
{ calories_per_20_grass = cp20g; }

int Herbivore::get_calories_per_flower()
{ return calories_per_flower; }

void Herbivore::set_calories_per_flower(int cpf)
{ calories_per_flower = cpf; }

int Herbivore::get_calories_per_30_flowers()
{ return calories_per_30_flowers; }

void Herbivore::set_calories_per_30_flowers(int cp30f)
{ calories_per_30_flowers = cp30f; }

int Herbivore::get_reproductive_rate()
{ return reproductive_rate; }

void Herbivore::set_reproductive_rate(int rr)
{ reproductive_rate = rr; }

int Herbivore::get_min_age_to_reproduce()
{ return min_age_to_reproduce; }

void Herbivore::set_min_age_to_reproduce(int mar)
{ min_age_to_reproduce = mar; }

int Herbivore::get_min_calories_to_reproduce()
{ return min_calories_to_reproduce; }

void Herbivore::set_min_calories_to_reproduce(int mcr)
{ min_calories_to_reproduce = mcr; }

int Herbivore::get_min_calories_to_evade()
{ return min_calories_to_evade; }

void Herbivore::set_min_calories_to_evade(int mce)
{ min_calories_to_evade = mce; }
