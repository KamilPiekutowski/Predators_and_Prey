#include "Empty.h"

Empty::Empty()
{

    set_curr_calories(25);
    set_max_calories(100);
    set_plant_rate(20);
    if(!image.loadFromFile("img/dirt.png")){
        cout << "Could not load image" << endl;
    image.create(TILE_SIZE,TILE_SIZE, sf::Color::Yellow);
    }
    this->texture.update(image);


}

Empty::~Empty()
{

}
