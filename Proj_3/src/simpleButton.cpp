#include "simpleButton.h"

simpleButton::simpleButton()
{
    Init("button",24,5,5);
}

simpleButton::simpleButton(String str)
{
    std::cout << "call 2nd constr" << std::endl;
    Init(str,24,5,5);

}

simpleButton::simpleButton(String str,int fSize,int posX, int posY)
{
    Init(str,fSize,posX,posY);
}




simpleButton::~simpleButton()
{
    //dtor
}
//getters

int simpleButton::Size()
{
    return this->fontSize;
}

void simpleButton::Init(String str,int fSize,int posX, int posY)
{
    std::cout << "call 3rd constr" << std::endl;
    if (!this->font.loadFromFile("font.ttf"))
    {
       std::cout << "Font file not found." << std::endl;
    }
    else {
        std::cout << "Font loaded." << std::endl;
    }


    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(fSize);
    text.setColor(sf::Color::White);
    text.setStyle(sf::Text::Regular);

    sf::Vector2f pos;
    pos.x = posX;
    pos.y = posY;
    text.setPosition(pos);
    posStart.x = pos.x;
    posStart.y = pos.y;

    //getting the sixe of text object
    sf::FloatRect r = text.getGlobalBounds();
    sf::Vector2f offset;
    offset.x = r.width;
    offset.y = r.height * 2;
    posEnd.x = posStart.x + offset.x;
    posEnd.y = posStart.y + offset.y;

    border.setPosition(pos);
    border.setSize(offset);
    border.setFillColor(sf::Color::Black);
    border.setOutlineThickness(5);
    border.setOutlineColor(sf::Color::White);
}

bool simpleButton::isHover(sf::Vector2i mousePos){
    return(mousePos.x >= posStart.x && mousePos.x <= posEnd.x &&
                mousePos.y >= posStart.y && mousePos.y <= posEnd.y);

}
