#include "Flower.h"
#include <iostream>


Flower::Flower()
{

    set_curr_calories(25);
    set_max_calories(100);
    set_plant_rate(30);
    image.create(TILE_SIZE,TILE_SIZE, sf::Color::Yellow);
    if(!image.loadFromFile("img/yellowgrass.png")){
        cout << "Could not load image" << endl;
    }

    this->texture.update(image);

}

Flower::~Flower()
{

}
