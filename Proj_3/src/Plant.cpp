#include "Plant.h"

using namespace std;

Plant::Plant()
{

    max_calories  = 100;
    curr_calories = 25;
    image.create(TILE_SIZE,TILE_SIZE, sf::Color::Yellow);
    this->texture.update(image);

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

void Plant::set_plant_rate(int r)
{ plant_rate = r;}

int Plant::get_plant_rate()
{ return plant_rate;}


