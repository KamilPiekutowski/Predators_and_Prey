#include "Bear.h"
#include "TILE.h"
#include <iostream>
using namespace std;

Bear::Bear()
{
    set_move_made(false);
    set_max_age(60);
    set_curr_age(0);
    set_max_calories(250);
    set_curr_calories(100);
    set_min_calories_to_eat(170);
    set_metabolic_rate(3);
    set_reproductive_rate(75);
    set_min_age_to_reproduce(20);
    set_min_calories_to_reproduce(175);
    set_min_calories_to_hunt(30);
    set_calories_per_deer(15);
    set_calories_per_rabbit(13);
    if(!image.loadFromFile("img/bear.png"))
    {
        cout << "Could not load image" << endl;
        image.create(TILE_SIZE,TILE_SIZE, sf::Color::Black);
    }
    this->texture.update(image);
}

Bear::~Bear(){}
