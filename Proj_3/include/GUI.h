#ifndef GUI_H
#define GUI_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "textButton.h"
#include "TILE.h"
#include "Square.h"
#include "Rabbit.h"
#include "Wolf.h"
#include "Bear.h"
#include "Factory.h"
#include "simpleButton.h"

// macros
#define NUMROWS     30 //30
#define NUMCOLS     40 //40
#define NUMRABBITS  15//15
#define NUMDEER     5//5
#define NUMWOLVES   3 //3
#define NUMBEAR     2 //2
#define NUMGRASS    1000
#define NUMFLOWERS  200 //200
#define FPS_RATE 16

//reproduction rates
/*
    Note: the greater the number the slimmer chance
*/
/*
#define RABBIT_REP_CHANCE 2
#define DEER_REP_CHANCE 5
#define WOLF_REP_CHANCE 2
#define BEAR_REP_CHANCE 1
*/
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
        /*
            textButton *close = new textButton("Close",24,5,10);
            textButton *start = new textButton("Start",24,100,10);
        */
        simpleButton *close = new simpleButton("img/close.png",100,700,0);
        simpleButton *start = new simpleButton("img/play.png",100,100,0);
        simpleButton *pauseButton = new simpleButton("img/pause.png",100,0,0);
        simpleButton *decreaseSpeed = new simpleButton("img/backward.png",100,250,0);
        simpleButton *increaseSpeed = new simpleButton("img/forward.png",100,350,0);

        Square grid[NUMROWS][NUMCOLS];
        void step();
        void animal_turn(int,int,char);
        void herbivore_turn(int,int,char);
        void carnivore_turn(int,int,char);
        vector<Ordered_Pair> get_neighbors_that_have_only_plants(int,int);
        vector<Ordered_Pair> get_neighbors_that_have_only_prey(int,int);
        Ordered_Pair get_neighbor_with_highest_caloric_yield(vector<Ordered_Pair>);
        Ordered_Pair get_random_move(vector<Ordered_Pair>);
        void determine_if_herbivore_will_reproduce(Herbivore*,char);
        void determine_if_carnivore_will_reproduce(Carnivore*,char);
        bool there_is_neighboring_predator(Ordered_Pair,Ordered_Pair,char);
        void herbivore_eats(Ordered_Pair,Herbivore*);
        void carnivore_eats(Ordered_Pair,Carnivore*,int,int);
        Ordered_Pair get_square_without_fellow_predators(int,int);
        char display_stats_check_for_end_of_program();
        bool prey_is_three_squares_away(Ordered_Pair&,int,int);
        bool prey_is_two_squares_away(Ordered_Pair&,int,int);
        void setSpeed(int);
        void print_ASCII(char);
    protected:
    private:
        bool isRunning = false;
        bool isStarted = false;
        int speed;

};



#endif // GUI_H
