#ifndef GUI_H
#define GUI_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "textButton.h"
#include "TILE.h"
#include "Square.h"
#include "Rabbit.h"
#include "Factory.h"

// macros
#define NUMROWS     30 //30
#define NUMCOLS     40 //40
#define NUMRABBITS  2 //15
#define NUMDEER     2//5
#define NUMWOLVES   0 //3
#define NUMBEAR     0 //2
#define NUMGRASS    1190
#define NUMFLOWERS  0 //200

typedef struct Ordered_Pair_struct
{
    int row;
    int col;
}Ordered_Pair;

class GUI
{
    public:
        int32_t timer = 0;
        GUI();
        virtual ~GUI();
        //methods
        void Run();
        void drawGrid();
        void populate_grid();
        void create_grass_and_flowers();
        void create_animals();
        Ordered_Pair* create_rabbit_array();
        Ordered_Pair* create_deer_array(Ordered_Pair*);
        //members
        sf::RenderWindow *app;
        textButton *close = new textButton("Close",24,5,10);
        textButton *start = new textButton("Start",24,100,10);
        Square grid[NUMROWS][NUMCOLS];
        void step();
        void animal_turn(int,int,char);
        void herbivore_turn(int,int,char);
        void carnivore_turn(int,int,char);
        vector<Ordered_Pair> get_neighbors_that_have_only_plants(int,int);
        Ordered_Pair get_neighbor_with_highest_caloric_yield(vector<Ordered_Pair>);
        bool determine_if_herbivore_will_reproduce(Herbivore*,char);
        bool there_is_neighboring_predator(Ordered_Pair,Ordered_Pair,char);
        void herbivore_eats(Ordered_Pair,Herbivore*);
        //void herbivore_reproduces(int,int);
        void print_ASCII(char);
    protected:
    private:
        bool isRunning = false;

};



#endif // GUI_H
