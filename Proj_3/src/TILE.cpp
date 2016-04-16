#include "TILE.h"

TILE::TILE()
{
    this->image.create(TILE_SIZE,TILE_SIZE, sf::Color::Transparent);
    this->texture.create(TILE_SIZE,TILE_SIZE);
    this->texture.update(this->image);
    this->sprite.setTexture(this->texture);
}

TILE::~TILE()
{
    //dtor
}


void TILE::setPostition(sf::Vector2f pos)
{
    this->sprite.setPosition(pos);
}

void TILE::setColor(sf::Color c)
{
    this->image.create(TILE_SIZE,TILE_SIZE,c);
    //this->texture.create(TILE_SIZE,TILE_SIZE);
    this->texture.update(this->image);
    this->sprite.setTexture(this->texture);
}

void TILE::setImage(sf::Image img){
    this->texture.update(img);
    this->sprite.setTexture(this->texture);
}
