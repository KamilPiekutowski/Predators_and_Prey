#include "Rabbit.h"
#include "Square.h"
#include <iostream>
#include "TILE.h"
using namespace std;

Rabbit::Rabbit()
{
    set_move_made(false);
    set_max_age(100000000);
    set_curr_age(0);
    set_max_calories(45);
    set_curr_calories(10);
    set_metabolic_rate(3);
    set_calories_per_grass(5);
    set_calories_per_20_grass(1);
    set_calories_per_flower(6);
    set_calories_per_30_flowers(2);
    set_reproductive_rate(0);
    set_min_age_to_reproduce(10);
    set_min_calories_to_reproduce(40);
    set_min_calories_to_evade(30);
    if(!image.loadFromFile("img/rabbit.png"))
    {
        cout << "Could not load image" << endl;
        image.create(TILE_SIZE,TILE_SIZE, sf::Color::Yellow);
    }
    this->texture.update(image);
}

Rabbit::~Rabbit(){}



