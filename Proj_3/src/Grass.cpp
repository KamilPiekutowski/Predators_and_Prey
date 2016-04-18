#include "Grass.h"
#include <iostream>

Grass::Grass()
{

    set_curr_calories(25);
    set_max_calories(100);
    set_plant_rate(20);
    if(!image.loadFromFile("img/grass.png")){
        cout << "Could not load image" << endl;
    image.create(TILE_SIZE,TILE_SIZE, sf::Color::Green);
    }
    this->texture.update(image);


}

Grass::~Grass()
{

}
