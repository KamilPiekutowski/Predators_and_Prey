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
        sf::Text text;
        sf::RectangleShape border;
        Vector2i posStart;
        Vector2i posEnd;
    protected:
    private:
        //methods
        void Init(String,int,int,int);

        int fontSize;
        String fontText;
        String fileName;
        sf::Font font;



};

#endif // SIMPLEBUTTON_H
