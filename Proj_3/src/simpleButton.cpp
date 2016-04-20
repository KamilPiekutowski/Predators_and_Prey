#include "simpleButton.h"

simpleButton::simpleButton()
{
    Init("button",24,5,5);
}

simpleButton::simpleButton(String filename)
{
    std::cout << "call 2nd constr" << std::endl;
    Init(fileName,24,5,5);

}

simpleButton::simpleButton(String filename,int fSize,int posX, int posY)
{
    Init(filename,fSize,posX,posY);
}




simpleButton::~simpleButton()
{
    //dtor
}
//getters

int simpleButton::Size()
{
    return this->size;
}

void simpleButton::Init(String filename,int size,int posX, int posY)
{
    std::cout << "call 3rd constr" << std::endl;
    if (!this->Image.loadFromFile(filename))
    {
       std::cout << "Font file not found." << std::endl;
    }
    else {
        std::cout << "Font loaded." << std::endl;
    }

    //Texture.create(size,size);
    Texture.create(size,size);
    Texture.update(Image);
    Sprite.setTexture(Texture);


    sf::Vector2f pos;
    pos.x = posX;
    pos.y = posY;
    Sprite.setPosition(pos);
    posStart.x = pos.x;
    posStart.y = pos.y;

    //getting the sixe of text object
    posEnd.x = posStart.x + size;
    posEnd.y = posStart.y + size;

}

bool simpleButton::isHover(sf::Vector2i mousePos){
    return(mousePos.x >= posStart.x && mousePos.x <= posEnd.x &&
                mousePos.y >= posStart.y && mousePos.y <= posEnd.y);

}
