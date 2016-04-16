#include "Living_Being.h"
#include <iostream>
using namespace std;

Living_Being::Living_Being()
{

}

Living_Being::~Living_Being()
{
    //dtor
}



void Living_Being::take_turn()
{
    //cout << "Inside animal turn..." << endl;
}


int Living_Being::get_curr_calories()
{
    return curr_calories;
}
//setters
void Living_Being::set_curr_calories(int c)
{
    curr_calories = c;
}
void Living_Being::remove_calories(int c)
{
    curr_calories = curr_calories - c;
}
sf::Image Living_Being::get_Image(){
    return image;
}

sf::Texture Living_Being::get_texture(){
    return texture;
}


