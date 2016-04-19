#ifndef SIMPLEBUTTON_H
#define SIMPLEBUTTON_H
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class simpleButton
{
    public:
        simpleButton();
        simpleButton(String);
        simpleButton(String,int,int,int);
        virtual ~simpleButton();

        //getters
        int Size();
        bool isHover(sf::Vector2i);

        //members
        sf::Image Image;
        sf::Texture Texture;
        sf::Sprite Sprite;
        Vector2i posStart;
        Vector2i posEnd;
    protected:
    private:
        //methods
        void Init(String,int,int,int);

        int size;
        String fileName;



};

#endif // SIMPLEBUTTON_H
