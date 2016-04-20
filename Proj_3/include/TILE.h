#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>
#define TILE_SIZE 20

class TILE
{
    public:
        TILE();
        virtual ~TILE();
        sf::Sprite sprite;

        //setters
        void setPostition(sf::Vector2f);
        void setColor(sf::Color);
        void setImage(sf::Image);
    protected:
    private:
        sf::Image image;
        sf::Texture texture;
};

#endif // TILE_H
