#include "Wolf.h"
#include "TILE.h"
#include <iostream>
using namespace std;


Wolf::Wolf()
{
    set_move_made(false);
    set_max_age(50);
    set_curr_age(0);
    set_max_calories(200);
    set_curr_calories(150);
    set_min_calories_to_eat(190);
    set_metabolic_rate(2);
    set_reproductive_rate(45);
    set_min_age_to_reproduce(25);
    set_min_calories_to_reproduce(120);
    set_min_calories_to_hunt(40);
    if(!image.loadFromFile("img/wolf.png"))
    {
        cout << "Could not load image" << endl;
        image.create(TILE_SIZE,TILE_SIZE, sf::Color::White);
    }
    this->texture.update(image);
}
Wolf::~Wolf(){}
