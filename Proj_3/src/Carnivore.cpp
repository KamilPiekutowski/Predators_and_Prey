#include "Carnivore.h"
#include <iostream>
using namespace std;

Carnivore::Carnivore()
{
    set_is_pregnant(false);
}

Carnivore::~Carnivore(){}

// inherited methods
void Carnivore::hunt(){}
void Carnivore::age()
{
    set_curr_age(get_curr_age()+1);
}

void Carnivore::die(){}
void Carnivore::hunger()
{
    set_curr_calories(get_curr_calories() - get_metabolic_rate());
    if(get_curr_calories() < 0) {
        set_curr_calories(0);
    }
}
void Carnivore::move(){}
void Carnivore::reproduce(){}
void Carnivore::eat(int e)
{
    set_curr_calories(get_curr_calories() + e);
}
void Carnivore::take_turn(){}

//getters/setters
void Carnivore::set_move_made(bool b)
{ move_made = b;}

bool Carnivore::get_move_made()
{ return move_made;}

int Carnivore::get_max_age()
{ return max_age; }

void Carnivore::set_max_age(int ma)
{ max_age = ma; }

int Carnivore::get_curr_age()
{ return curr_age; }

void Carnivore::set_curr_age(int ca)
{ curr_age = ca; }

int Carnivore::get_max_calories()
{ return max_calories; }

void Carnivore::set_max_calories(int mc)
{ max_calories = mc; }

int Carnivore::get_curr_calories()
{ return curr_calories; }

void Carnivore::set_curr_calories(int cc)
{ curr_calories = cc; }

void Carnivore::set_min_calories_to_eat(int n)
{ min_calories_to_eat = n;}

int Carnivore::get_min_calories_to_eat()
{ return min_calories_to_eat;}

int Carnivore::get_metabolic_rate()
{ return metabolic_rate; }

void Carnivore::set_metabolic_rate(int mr)
{ metabolic_rate = mr; }

void Carnivore::set_calories_per_rabbit(int c)
{ calories_per_rabbit = c;}

int Carnivore::get_calories_per_rabbit()
{ return calories_per_rabbit;}

void Carnivore::set_calories_per_deer(int c)
{ calories_per_deer = c;}

int Carnivore::get_calories_per_deer()
{ return calories_per_deer;}

int Carnivore::get_reproductive_rate()
{ return reproductive_rate; }

void Carnivore::set_reproductive_rate(int rr)
{ reproductive_rate = rr; }

int Carnivore::get_min_age_to_reproduce()
{ return min_age_to_reproduce; }

void Carnivore::set_min_age_to_reproduce(int mar)
{ min_age_to_reproduce = mar; }

int Carnivore::get_min_calories_to_reproduce()
{ return min_calories_to_reproduce; }

void Carnivore::set_min_calories_to_reproduce(int mcr)
{ min_calories_to_reproduce = mcr; }

bool Carnivore::get_is_pregnant()
{ return is_pregnant;}

void Carnivore::set_is_pregnant(bool p)
{ is_pregnant = p;}

void Carnivore::set_min_calories_to_hunt(int s)
{   min_calories_to_hunt = s;}

int Carnivore::get_min_calories_to_hunt()
{   return min_calories_to_hunt;}
