#ifndef GUI_H
#define GUI_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "textButton.h"
#include "TILE.h"
#include "Square.h"
#include "Rabbit.h"

// macros
#define NUMROWS     30 //30
#define NUMCOLS     40 //40
#define NUMRABBITS  10 //15
#define NUMDEER     0 //5
#define NUMWOLVES   0 //3
#define NUMBEAR     0 //2
#define NUMGRASS    999
#define NUMFLOWERS  2 //200

typedef struct Ordered_Pair_struct
{
    int row;
    int col;
}Ordered_Pair;

class GUI
{
    public:
        GUI();
        virtual ~GUI();
        //methods
        void Run();
        void drawGrid();
        void populate_grid();
        Ordered_Pair* create_grass_array();
        Ordered_Pair* create_rabbit_array();
        //members
        sf::RenderWindow *app;
        textButton *close = new textButton("Close",24,5,10);
        textButton *start = new textButton("Start",24,100,10);
        Square grid[NUMROWS][NUMCOLS];
        void step();
        void animal_turn(int,int,char);
        void rabbit_turn(int,int);
        void dear_turn(int,int);
        void bear_turn(int,int);
        void wolf_turn(int,int);
        vector<Ordered_Pair> get_neighbors_that_have_only_plants(int,int);
        Ordered_Pair get_neighbor_with_highest_caloric_yield(vector<Ordered_Pair>);
        bool determine_if_rabbit_will_reproduce(Rabbit*);
        bool there_is_neighboring_predator(Ordered_Pair,Ordered_Pair,char);
        void rabbit_eats(Ordered_Pair,Rabbit*);
        void rabbit_reproduces(int,int);
    protected:
    private:

};



#endif // GUI_H