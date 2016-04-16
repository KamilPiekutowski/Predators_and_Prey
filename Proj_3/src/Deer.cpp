#include "Deer.h"



Deer::Deer()
{
    /*
    set_move_made(false);
    set_max_age(30);
    set_curr_age(0);
    set_max_calories(55);
    set_curr_calories(0);
    set_metabolic_rate(4);
    set_calories_per_grass(5);
    set_calories_per_20_grass(2);
    set_calories_per_flower(6);
    set_calories_per_30_flowers(3);
    set_reproductive_rate(40);
    set_min_age_to_reproduce(12);
    set_min_calories_to_reproduce(40);
    set_min_calories_to_evade(35);
    */
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
    image.create(TILE_SIZE,TILE_SIZE, sf::Color::Blue);
    if(!image.loadFromFile("img/deer.png")){
        cout << "Could not load image" << endl;

    }
    this->texture.update(image);
}

Deer::~Deer()
{
    //dtor
}
