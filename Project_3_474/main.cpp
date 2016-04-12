#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include "Square.h"
#define NUMROWS     2 //30
#define NUMCOLS     2 //40
#define NUMRABBITS  1 //15
#define NUMDEER     0 //5
#define NUMWOLVES   0 //3
#define NUMBEAR     0 //2
#define NUMGRASS    2 //999
#define NUMFLOWERS  2 //200
using namespace std;

void engine();
Square **initialize_board();
Ordered_Pair *create_grass_array();
Ordered_Pair *create_flower_array(Ordered_Pair*);
Ordered_Pair *create_rabbit_array();
Ordered_Pair *create_deer_array(Ordered_Pair*);
Ordered_Pair *create_wolf_array(Ordered_Pair*,Ordered_Pair*);
Ordered_Pair *create_bear_array(Ordered_Pair*,Ordered_Pair*,Ordered_Pair*);
void insert_beings_into_board(Square**,Ordered_Pair*,Ordered_Pair*,Ordered_Pair*,Ordered_Pair*,Ordered_Pair*,Ordered_Pair*);
bool should_insert(Square **,Ordered_Pair*,int,int,int);
void insert_grass(Square**,int,int);
void insert_flower(Square**,int,int);
void insert_rabbit(Square**,int,int);
void insert_deer(Square**,int,int);
void insert_wolf(Square**,int,int);
void insert_bear(Square**,int,int);
void print_board(Square**);
void print_random_arrays(Ordered_Pair*,Ordered_Pair*,Ordered_Pair*,Ordered_Pair*,Ordered_Pair*,Ordered_Pair*);
void print_array(Ordered_Pair*,int);
int get_num_turns();
void failed_insert_sanity_check(string);
void take_turn(Square**);
void grass_turn(Square**,int,int);
void flower_turn(Square**,int,int);
void rabbit_turn(Square**,int,int);
void deer_turn(Square**,int,int);
void wolf_turn(Square**,int,int);
void bear_turn(Square**,int,int);
void remove_animal_from_square(Square **, int, int, string);
void remove_being_from_square_sanity_check_fail(string);
vector<Ordered_Pair> get_neighbors_that_have_only_plants(Square **, int, int);
Ordered_Pair get_neighbor_with_highest_caloric_yield(Square**,vector<Ordered_Pair>&);
bool determine_if_rabbit_will_reproduce(Rabbit*);
bool determine_if_deer_will_reproduce(Deer*);
void move_rabbit_to_new_square(Square**,Ordered_Pair,Rabbit*);
bool there_is_neighboring_predator(Square**,Ordered_Pair,Ordered_Pair,char&);
void rabbit_eats(Square**,Ordered_Pair,Rabbit*);
void remove_grass(Square**,Ordered_Pair);
void remove_flower(Square**,Ordered_Pair);
void rabbit_reproduces(Square**,int,int);
bool rabbit_fleeing_is_option(Square **, Ordered_Pair, char, Rabbit *);
void rabbit_flees(Square**,Rabbit*,Ordered_Pair,char);
void move_deer_to_square(Square**,Ordered_Pair,Deer*);
void deer_eats(Square**,Ordered_Pair,Deer*);
void deer_reproduces(Square**,int,int);
void deer_flees(Square**,Deer*,Ordered_Pair,char);
bool deer_fleeing_is_option(Square**,Ordered_Pair,char,Deer*);
bool determine_if_wolf_will_reproduce(Wolf*);
vector<Ordered_Pair> get_neighbors_that_have_only_prey(Square**,int,int);
void move_wolf_to_new_square(Square**,Ordered_Pair,Wolf*);
void wolf_eat(Square**,Ordered_Pair,Wolf*);
bool is_prey_within_two_squares(Square**,int,int,Ordered_Pair&);
bool is_prey_within_three_squares(Square**,int,int,Ordered_Pair&);
bool check_neighbors_for_unoccupied_square(Square**,int,int,Ordered_Pair&);
void wolf_reproduce(Square**,int,int);
void print_value_of_square(Square**,int,int);
bool determine_if_bear_will_reproduce(Bear*);
void move_bear_to_new_square(Square**,Ordered_Pair,Bear*);
void bear_eat(Square**,Ordered_Pair,Bear*);
void bear_reproduce(Square**,int,int);
bool is_prey_within_four_squares(Square**,int,int,Ordered_Pair);
void reset_indices(Square**);

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("cb.bmp"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            engine();
            if (event.type == sf::Event::Closed)
                app.close();
        }

        // Clear screen
        app.clear();

        // Draw the sprite
        app.draw(sprite);

        // Update the window
        app.display();
    }
    return EXIT_SUCCESS;
}

void engine()
{
    // initialize the board
    Square** board = initialize_board();

    // create random arrays for the initial creation of the beings
    Ordered_Pair* grass_array  = create_grass_array();
    Ordered_Pair* flower_array = create_flower_array(grass_array);
    Ordered_Pair* rabbit_array = create_rabbit_array();
    Ordered_Pair* deer_array   = create_deer_array(rabbit_array);
    Ordered_Pair* wolf_array   = create_wolf_array(rabbit_array, deer_array);
    Ordered_Pair* bear_array   = create_bear_array(rabbit_array, deer_array, wolf_array);

    // print the random arrays to make sure that yes, they are random
    print_random_arrays(grass_array, flower_array, rabbit_array, deer_array, wolf_array, bear_array);

    // insert into animals into the board
    insert_beings_into_board(board, grass_array, flower_array, rabbit_array,
                             deer_array, wolf_array, bear_array);

    // print the initial state of the board
    cout << "Initial board state:" << endl;
    print_board(board);

    // get the number of turns for the program to take
    int num_turns = get_num_turns();

    //
    // now let's start the moves -- we'll go through each square on the board, and have whatever is there
    // makes a move
    //
    int time = 0;
    while (time < num_turns)
    {
        take_turn(board);
        time++;
    }
}

void take_turn(Square **board)
{

    for (int row = 0; row < NUMROWS; row++)
    {
        for (int col = 0; col < NUMCOLS; col++)
        {
            //
            // determine what pieces should move
            //
            if (board[row][col].get_grass())
            {
                grass_turn(board, row, col);
            }
            else if(board[row][col].get_flower())
            {
                flower_turn(board, row, col);
            }
            else if (board[row][col].get_rabbit())
            {
                rabbit_turn(board, row, col);
            }
            else if (board[row][col].get_deer())
            {
                deer_turn(board, row, col);
            }
            else if (board[row][col].get_wolf())
            {
                wolf_turn(board, row, col);
            }
            else if (board[row][col].get_bear())
            {
                bear_turn(board, row, col);
            }
            else if (board[row][col].get_grass_rabbit())
            {
                grass_turn(board, row, col);
                rabbit_turn(board, row, col);
            }
            else if (board[row][col].get_grass_deer())
            {
                grass_turn(board, row, col);
                deer_turn(board, row, col);
            }
            else if (board[row][col].get_grass_wolf())
            {
                grass_turn(board, row, col);
                wolf_turn(board, row, col);
            }
            else if (board[row][col].get_grass_bear())
            {
                grass_turn(board, row, col);
                bear_turn(board, row, col);
            }
            else if (board[row][col].get_flower_rabbit())
            {
                flower_turn(board, row, col);
                rabbit_turn(board, row, col);
            }
            else if (board[row][col].get_flower_deer())
            {
                flower_turn(board, row, col);
                deer_turn(board, row, col);
            }
            else if (board[row][col].get_flower_wolf())
            {
                flower_turn(board, row, col);
                wolf_turn(board, row, col);
            }
            else if (board[row][col].get_flower_bear())
            {
                flower_turn(board, row, col);
                bear_turn(board, row, col);
            }
            else if (board[row][col].get_empty())
            {
            }
            else
            {
                cout << "FAILED SANITY CHECK in take_turn()" << endl;
                cout << "Conditions were not met." << endl;
                exit(EXIT_FAILURE);
            }

            print_board(board);
            cout << "\t\tEnd of move on\t(" << row << ", " << col << ")" << endl;
            print_value_of_square(board, row, col);
            cout << "**********************************************************" << endl;
        }
    }

    //
    // now that the round is done, we need to go back and reset all of the animals indices
    //
    cout << "End of round..." << endl;
    reset_indices(board);
}

void reset_indices(Square **board)
{
    for (int row = 0; row < NUMROWS; row++)
    {
        for (int col = 0; col < NUMCOLS; col++)
        {
            if (board[row][col].get_rabbit() ||
                board[row][col].get_grass_rabbit() ||
                board[row][col].get_flower_rabbit())
            {
                Rabbit* r = (Rabbit*)board[row][col].get_animal();
                r->set_index(0);
                board[row][col].set_animal(r);
            }
            if (board[row][col].get_deer() ||
                board[row][col].get_grass_deer() ||
                board[row][col].get_flower_deer())
            {
                Deer *d = (Deer*)board[row][col].get_animal();
                d->set_index(0);
                board[row][col].set_animal(d);
            }
            if (board[row][col].get_wolf() ||
                board[row][col].get_grass_wolf() ||
                board[row][col].get_flower_wolf())
            {
                Wolf *w = (Wolf*)board[row][col].get_animal();
                w->set_index(0);
                board[row][col].set_animal(w);
            }
            if (board[row][col].get_bear() ||
                board[row][col].get_grass_bear() ||
                board[row][col].get_flower_bear())
            {
                Bear *b = (Bear*)board[row][col].get_animal();
                b->set_index(0);
                board[row][col].set_animal(b);
            }
        }
    }
}

void bear_turn(Square **board, int row, int col)
{
    // get the bear
    Bear* b = (Bear*)board[row][col].get_animal();
    b->set_index(b->get_index()+1);
    if (b->get_index()%2 == 1)
    {
        b->hunger();
        b->age();
        if (b->get_curr_calories() == 0 || b->get_curr_age() == b->get_max_age())
        {
            remove_animal_from_square(board, row, col, "bear");
        }
        else
        {
            bool bear_will_reproduce = determine_if_bear_will_reproduce(b);

            if (b->get_curr_calories() < b->get_min_calories_to_eat())
            {
                vector<Ordered_Pair> neighbors = get_neighbors_that_have_only_prey(board, row, col);
                if (!neighbors.empty())
                {
                    Ordered_Pair destination = neighbors.at(0);
                    remove_animal_from_square(board, row, col, "bear");
                    move_bear_to_new_square(board, destination, b);
                    bear_eat(board, destination, b);
                    if (bear_will_reproduce) bear_reproduce(board, row, col);
                }
                else if (b->get_min_calories_to_hunt() >= b->get_curr_calories())
                {
                    Ordered_Pair new_destination;
                    if (is_prey_within_two_squares(board, row, col, new_destination))
                    {
                        move_bear_to_new_square(board, new_destination, b);
                    }
                    else if (is_prey_within_three_squares(board, row, col, new_destination))
                    {
                        move_bear_to_new_square(board, new_destination, b);
                    }
                    else if (is_prey_within_four_squares(board, row, col, new_destination))
                    {
                        move_bear_to_new_square(board, new_destination, b);
                    }
                    else
                    {
                        if (check_neighbors_for_unoccupied_square(board, row, col, new_destination))
                        {
                            move_bear_to_new_square(board, new_destination, b);
                        }
                    }
                }
            }
        }
    }
}

void wolf_turn(Square **board, int row, int col)
{
    // get the wolf
    Wolf* w = (Wolf*)board[row][col].get_animal();
    w->set_index(w->get_index()+1);
    if (w->get_index()%2 == 1)
    {
        //
        // see if the wolf dies from hunger.  If it doesn't,
        // we continue the turn, else, we kill the wolf.
        //
        w->hunger();
        w->age();
        if (w->get_curr_calories() == 0 || w->get_curr_age() == w->get_max_age())
        {
            remove_animal_from_square(board, row, col, "wolf");
        }
        else // the wolf hasn't died from hunger
        {
            bool wolf_will_reproduce = determine_if_wolf_will_reproduce(w);
            //
            // * if the wolf's calories are <= 190, it's hungry, and will
            //   check neighboring squares for food.
            // * If it's fat and happy, it will just wander to the nearest
            //   unoccupied square.
            // * If there isn't an unoccupied square, it'll stay put.
            // * If there ins't food in a neighboring square and the wolf
            //   is starving (< 40), it will hunt.
            // * to hunt, it will look for food within 3 square.  If there
            //   is square within 3 squares, it'll move NEXT to the square,
            //   provided that the square is emtpy.
            //
            if (w->get_curr_calories() <= w->get_min_calories_to_eat())
            {
                vector<Ordered_Pair> neighbors = get_neighbors_that_have_only_prey(board, row, col);

                // if there are neighboring prey, we eat the first animal that comes along...
                if (!neighbors.empty())
                {
                    // get the destination coordinates
                    Ordered_Pair destination = neighbors.at(0);

                    // remove the wolf from it's current square
                    remove_animal_from_square(board, row, col, "wolf");

                    // move the wolf to it's destination square and determine what it is that we're eating
                    move_wolf_to_new_square(board, destination, w);

                    // dine!
                    wolf_eat(board, destination, w);

                    // reproduce
                    if (wolf_will_reproduce)
                    {
                        wolf_reproduce(board, row, col);
                    }
                }
                    // else we see if we can hunt
                else if (w->get_min_calories_to_hunt() >= w->get_curr_calories())
                {
                    // first, see if there's prey within two spots of the wolf...
                    Ordered_Pair new_destination;
                    if (is_prey_within_two_squares(board, row, col, new_destination))
                    {
                        move_wolf_to_new_square(board, new_destination, w);
                    }
                    else if (is_prey_within_three_squares(board, row, col, new_destination))
                    {
                        move_wolf_to_new_square(board, new_destination, w);
                    }
                    else
                    {
                        //
                        // if we get here, then although the wolf is able to hunt, there isn't
                        // anything to hunt.  We already know that none of the neighbors have prey,
                        // so we just move the wolf to the first unoccupied square in this order:
                        // up, down, left, right
                        //
                        if (check_neighbors_for_unoccupied_square(board, row, col, new_destination))
                        {
                            move_wolf_to_new_square(board, new_destination, w);
                        }
                    }
                }
            }
        }
    }
}

/**
 * See the rabbit's turn for comments, as the moves are the
 * same.
 */
void deer_turn(Square **board, int row, int col)
{
    Deer* d = (Deer*)board[row][col].get_animal();
    d->set_index(d->get_index()+1);
    if (d->get_index()%2 == 1)
    {
        d->hunger();
        d->age();
        if (d->get_curr_calories() == 0 || d->get_curr_age() == d->get_max_age())
        {
            remove_animal_from_square(board, row, col, "deer");
        }
        else
        {
            vector<Ordered_Pair> neighbors = get_neighbors_that_have_only_plants(board, row, col);
            if (!neighbors.empty())
            {
                Ordered_Pair destination = get_neighbor_with_highest_caloric_yield(board, neighbors);
                bool will_reproduce_this_turn = determine_if_deer_will_reproduce(d);
                remove_animal_from_square(board, row, col, "deer");
                move_deer_to_square(board, destination, d);
                Ordered_Pair neighboring_predator;
                neighboring_predator.col = -999;
                neighboring_predator.row = -999;
                char direction = ' ';
                if (!there_is_neighboring_predator(board, destination, neighboring_predator, direction))
                {
                    if (d->get_curr_calories() < d->get_max_calories())
                    {
                        deer_eats(board, destination, d);
                    }
                    if (will_reproduce_this_turn)
                    {
                        deer_reproduces(board, row, col);
                    }
                }
                else //  we need to flee
                {
                    // so we need to check if there is anything in two squares in the
                    // OPPOSITE direction of the predator.
                    if (deer_fleeing_is_option(board, destination, direction, d))
                    {
                        deer_flees(board, d, destination, direction);
                    }
                }
            }
        }
    }
}

void rabbit_turn(Square **board, int row, int col)
{
    // get the rabbit, see if it's turn is finished
    Rabbit* r = (Rabbit*)board[row][col].get_animal();
    r->set_index(r->get_index()+1);
    if (r->get_index()%2 == 1)
    {
        // run the hunger() method.  If the animal dies, end of turn
        r->hunger();
        r->age();
        if (r->get_curr_calories() < 1 || r->get_curr_age() == r->get_max_age())
        {
            remove_animal_from_square(board, row, col, "rabbit");
        }
        else // the turn continues
        {
            // get the squares that it could possibly move to
            vector<Ordered_Pair> neighbors = get_neighbors_that_have_only_plants(board, row, col);

            if (!neighbors.empty()) // else the turn ends
            {
                // next we need to figure out the neighbor with the highest caloric yield
                Ordered_Pair destination = get_neighbor_with_highest_caloric_yield(board, neighbors);

                // next, will we reproduce in this turn
                bool will_reproduce_this_turn = determine_if_rabbit_will_reproduce(r);

                // next, we need to actually move to the destination
                remove_animal_from_square(board, row, col, "rabbit");
                move_rabbit_to_new_square(board, destination, r);


                //
                // now that we've moved there, we check for a neighboring predator.  If there
                // is one, we flee.  If there is not, we eat, possibly reproduce, and end turn.
                //
                Ordered_Pair neighboring_predator;
                neighboring_predator.col = -999;
                neighboring_predator.row = -999;
                char direction = ' ';
                if (!there_is_neighboring_predator(board, destination, neighboring_predator, direction))
                {
                    // next the rabbit needs to eat
                    if (r->get_curr_calories() < r->get_max_calories())
                    {
                        rabbit_eats(board, destination, r);
                    }

                    // then the rabbit needs to reproduce
                    if (will_reproduce_this_turn)
                    {
                        rabbit_reproduces(board, row, col);
                    }
                }
                else //  we need to flee
                {
                    // so we need to check if there is anything in two squares in the
                    // OPPOSITE direction of the predator.
                    if (rabbit_fleeing_is_option(board, destination, direction, r))
                    {
                        rabbit_flees(board, r, destination, direction);
                    }
                }
            }
        }
    }
}

bool check_neighbors_for_unoccupied_square(Square **board, int row, int col, Ordered_Pair& dest)
{
    // look up
    if (col-1 <= 0)
    {
        if (board[row][col-1].get_grass() || board[row][col-1].get_flower())
        {
            dest.row = row;
            dest.col = col-1;
            return true;
        }
    }

    // down down
    if (col+1 < NUMCOLS)
    {
        if (board[row][col+1].get_grass() || board[row][col+1].get_flower())
        {
            dest.row = row;
            dest.col = col+1;
            return true;
        }
    }

    // look left
    if (row-1 >= 0)
    {
        if (board[row-1][col].get_grass() || board[row-1][col].get_flower())
        {
            dest.row = row-1;
            dest.col = col;
            return true;
        }
    }

    // look right
    if (row+1 < NUMROWS)
    {
        if (board[row+1][col].get_grass() || board[row+1][col].get_flower())
        {
            dest.row = row+1;
            dest.col = col;
            return true;
        }
    }
    return false;
}

bool is_prey_within_two_squares(Square **board, int row, int col, Ordered_Pair& dest)
{
    // look up
    if (row-2 >= 0)
    {
        if (board[row-2][col].get_rabbit()        ||
            board[row-2][col].get_grass_rabbit()  ||
            board[row-2][col].get_flower_rabbit() ||
            board[row-2][col].get_deer()          ||
            board[row-2][col].get_grass_deer()    ||
            board[row-2][col].get_flower_deer())
        {
            dest.row = row-1;
            dest.col = col;
            return true;
        }
    }

    // look down
    if (row + 2 < NUMROWS)
    {
        if (board[row+2][col].get_rabbit()        ||
            board[row+2][col].get_grass_rabbit()  ||
            board[row+2][col].get_flower_rabbit() ||
            board[row+2][col].get_deer()          ||
            board[row+2][col].get_grass_deer()    ||
            board[row+2][col].get_flower_deer())
        {
            dest.row = row+1;
            dest.col = col;
            return true;
        }
    }

    // look left
    if (col-2 >= 0)
    {
        if (board[row][col-2].get_rabbit()        ||
            board[row][col-2].get_grass_rabbit()  ||
            board[row][col-2].get_flower_rabbit() ||
            board[row][col-2].get_deer()          ||
            board[row][col-2].get_grass_deer()    ||
            board[row][col-2].get_flower_deer())
        {
            dest.row = row;
            dest.col = col-1;
            return true;
        }
    }

    // look right
    if (col+2 < NUMCOLS)
    {
        if (board[row+2][col].get_rabbit()        ||
            board[row+2][col].get_grass_rabbit()  ||
            board[row+2][col].get_flower_rabbit() ||
            board[row+2][col].get_deer()          ||
            board[row+2][col].get_grass_deer()    ||
            board[row+2][col].get_flower_deer())
        {
            dest.row = row+1;
            dest.col = col;
            return true;
        }
    }
    return false;
}

bool is_prey_within_three_squares(Square **board, int row, int col, Ordered_Pair& dest)
{
    // look up
    if (row-3 >= 0)
    {
        if (board[row-3][col].get_rabbit()        ||
            board[row-3][col].get_grass_rabbit()  ||
            board[row-3][col].get_flower_rabbit() ||
            board[row-3][col].get_deer()          ||
            board[row-3][col].get_grass_deer()    ||
            board[row-3][col].get_flower_deer())
        {
            dest.row = row-2;
            dest.col = col;
            return true;
        }
    }

    // look down
    if (row + 3 < NUMROWS)
    {
        if (board[row+3][col].get_rabbit()        ||
            board[row+3][col].get_grass_rabbit()  ||
            board[row+3][col].get_flower_rabbit() ||
            board[row+3][col].get_deer()          ||
            board[row+3][col].get_grass_deer()    ||
            board[row+3][col].get_flower_deer())
        {
            dest.row = row+2;
            dest.col = col;
            return true;
        }
    }

    // look left
    if (col-3 >= 0)
    {
        if (board[row][col-3].get_rabbit()        ||
            board[row][col-3].get_grass_rabbit()  ||
            board[row][col-3].get_flower_rabbit() ||
            board[row][col-3].get_deer()          ||
            board[row][col-3].get_grass_deer()    ||
            board[row][col-3].get_flower_deer())
        {
            dest.row = row;
            dest.col = col-2;
            return true;
        }
    }

    // look right
    if (col+3 < NUMCOLS)
    {
        if (board[row+3][col].get_rabbit()        ||
            board[row+3][col].get_grass_rabbit()  ||
            board[row+3][col].get_flower_rabbit() ||
            board[row+3][col].get_deer()          ||
            board[row+3][col].get_grass_deer()    ||
            board[row+3][col].get_flower_deer())
        {
            dest.row = row+2;
            dest.col = col;
            return true;
        }
    }
    return false;
}

bool is_prey_within_four_squares(Square **board, int row, int col, Ordered_Pair dest)
{
    // look up
    if (row-4 >= 0)
    {
        if (board[row-4][col].get_rabbit()        ||
            board[row-4][col].get_grass_rabbit()  ||
            board[row-4][col].get_flower_rabbit() ||
            board[row-4][col].get_deer()          ||
            board[row-4][col].get_grass_deer()    ||
            board[row-4][col].get_flower_deer())
        {
            dest.row = row-3;
            dest.col = col;
            return true;
        }
    }

    // look down
    if (row+4 < NUMROWS)
    {
        if (board[row+4][col].get_rabbit()        ||
            board[row+4][col].get_grass_rabbit()  ||
            board[row+4][col].get_flower_rabbit() ||
            board[row+4][col].get_deer()          ||
            board[row+4][col].get_grass_deer()    ||
            board[row+4][col].get_flower_deer())
        {
            dest.row = row+3;
            dest.col = col;
            return true;
        }
    }

    // look left
    if (col-4 >= 0)
    {
        if (board[row][col-4].get_rabbit()        ||
            board[row][col-4].get_grass_rabbit()  ||
            board[row][col-4].get_flower_rabbit() ||
            board[row][col-4].get_deer()          ||
            board[row][col-4].get_grass_deer()    ||
            board[row][col-4].get_flower_deer())
        {
            dest.row = row;
            dest.col = col-3;
            return true;
        }
    }

    // look right
    if (col+4 < NUMCOLS)
    {
        if (board[row+4][col].get_rabbit()        ||
            board[row+4][col].get_grass_rabbit()  ||
            board[row+4][col].get_flower_rabbit() ||
            board[row+4][col].get_deer()          ||
            board[row+4][col].get_grass_deer()    ||
            board[row+4][col].get_flower_deer())
        {
            dest.row = row+3;
            dest.col = col;
            return true;
        }
    }
    return false;
}

void rabbit_flees(Square **board, Rabbit *r, Ordered_Pair dest, char direction)
{
    if ('l' == direction)
    {
        dest.col = dest.col-2;
    }
    if ('u' == direction)
    {
        dest.row = dest.row-2;
    }
    if ('r' == direction)
    {
        dest.col = dest.col+2;
    }
    if ('d' == direction)
    {
        dest.row = dest.row+2;
    }
    remove_animal_from_square(board, dest.row, dest.col, "rabbit");
    move_rabbit_to_new_square(board, dest, r);
}

void deer_flees(Square **board, Deer *d, Ordered_Pair dest, char direction)
{
    if ('l' == direction)
    {
        dest.col = dest.col-2;
    }
    if ('u' == direction)
    {
        dest.row = dest.row-2;
    }
    if ('r' == direction)
    {
        dest.col = dest.col+2;
    }
    if ('d' == direction)
    {
        dest.row = dest.row+2;
    }
    remove_animal_from_square(board, dest.row, dest.col, "deer");
    move_deer_to_square(board, dest, d);
}

bool rabbit_fleeing_is_option(Square **board, Ordered_Pair dest, char direction, Rabbit *r)
{
    // see if the rabbit has the calories to flee
    if (r->get_curr_calories() >= r->get_min_calories_to_evade())
    {
        // if left is the predator, go right
        if ('l' == direction && dest.col+2 < NUMCOLS)
        {
            if (board[dest.row][dest.col+2].get_empty() ||
                board[dest.row][dest.col+2].get_grass() ||
                board[dest.row][dest.col+2].get_flower())
            {
                return true;
            }
        }

        // if up is the predator, go down
        if ('u' == direction && dest.row+2 < NUMROWS)
        {
            if (board[dest.row+2][dest.col].get_empty() ||
                board[dest.row+2][dest.col].get_grass() ||
                board[dest.row+2][dest.col].get_flower())
            {
                return true;
            }
        }

        // if right is the predator, go left
        if ('r' == direction && dest.col-2 >= 0)
        {
            if (board[dest.row][dest.col-2].get_empty() ||
                board[dest.row][dest.col-2].get_grass() ||
                board[dest.row][dest.col-2].get_flower())
            {
                return true;
            }
        }

        // if down in the predator, go up
        if ('d' == direction && dest.row-2 >= 0)
        {
            if (board[dest.row+2][dest.col].get_empty() ||
                board[dest.row+2][dest.col].get_grass() ||
                board[dest.row+2][dest.col].get_flower())
            {
                return true;
            }
        }
    }
    return false;
}

bool deer_fleeing_is_option(Square **board, Ordered_Pair dest, char direction, Deer *d)
{
    // see if the deer has the calories to flee
    if (d->get_curr_calories() >= d->get_min_calories_to_evade())
    {
        // if left is the predator, go right
        if ('l' == direction && dest.col+2 < NUMCOLS)
        {
            if (board[dest.row][dest.col+2].get_empty() ||
                board[dest.row][dest.col+2].get_grass() ||
                board[dest.row][dest.col+2].get_flower())
            {
                return true;
            }
        }

        // if up is the predator, go down
        if ('u' == direction && dest.row+2 < NUMROWS)
        {
            if (board[dest.row+2][dest.col].get_empty() ||
                board[dest.row+2][dest.col].get_grass() ||
                board[dest.row+2][dest.col].get_flower())
            {
                return true;
            }
        }

        // if right is the predator, go left
        if ('r' == direction && dest.col-2 >= 0)
        {
            if (board[dest.row][dest.col-2].get_empty() ||
                board[dest.row][dest.col-2].get_grass() ||
                board[dest.row][dest.col-2].get_flower())
            {
                return true;
            }
        }

        // if down in the predator, go up
        if ('d' == direction && dest.row-2 >= 0)
        {
            if (board[dest.row+2][dest.col].get_empty() ||
                board[dest.row+2][dest.col].get_grass() ||
                board[dest.row+2][dest.col].get_flower())
            {
                return true;
            }
        }
    }
    return false;
}

void rabbit_reproduces(Square **board, int row, int col)
{
    // first we need to know if the baby rabbit will be created on a flower, grass, or empty
    if (board[row][col].get_grass())
    {
        board[row][col].set_grass(false);
        board[row][col].set_grass_rabbit(true);
        board[row][col].set_identifier('R');
    }
    else if (board[row][col].get_flower())
    {
        board[row][col].set_flower(false);
        board[row][col].set_flower_rabbit(true);
        board[row][col].set_identifier('F');
    }
    else if(board[row][col].get_empty())
    {
        board[row][col].set_empty(false);
        board[row][col].set_rabbit(true);
        board[row][col].set_identifier('r');
    }
    board[row][col].set_animal(Living_Being_Factory::create_being('r'));
}

void deer_reproduces(Square **board, int row, int col)
{
    // first we need to know if the baby deer will be created on a flower, grass, or empty
    if (board[row][col].get_grass())
    {
        board[row][col].set_grass(false);
        board[row][col].set_grass_deer(true);
        board[row][col].set_identifier('D');
    }
    else if (board[row][col].get_flower())
    {
        board[row][col].set_flower(false);
        board[row][col].set_flower_deer(true);
        board[row][col].set_identifier('E');
    }
    else if(board[row][col].get_empty())
    {
        board[row][col].set_empty(false);
        board[row][col].set_deer(true);
        board[row][col].set_identifier('d');
    }
    board[row][col].set_animal(Living_Being_Factory::create_being('d'));
}

void wolf_reproduce(Square **board, int row, int col)
{
    // first we need to know if the baby wolf will be created on a flower, grass, or empty
    if (board[row][col].get_grass())
    {
        board[row][col].set_grass(false);
        board[row][col].set_grass_wolf(true);
        board[row][col].set_identifier('D');
    }
    else if (board[row][col].get_flower())
    {
        board[row][col].set_flower(false);
        board[row][col].set_flower_wolf(true);
        board[row][col].set_identifier('G');
    }
    else if(board[row][col].get_empty())
    {
        board[row][col].set_empty(false);
        board[row][col].set_wolf(true);
        board[row][col].set_identifier('W');
    }
    board[row][col].set_animal(Living_Being_Factory::create_being('w'));
}

void bear_reproduce(Square **board, int row, int col)
{
    // first we need to know if the baby wolf will be created on a flower, grass, or empty
    if (board[row][col].get_grass())
    {
        board[row][col].set_grass(false);
        board[row][col].set_grass_bear(true);
        board[row][col].set_identifier('Y');
    }
    else if (board[row][col].get_flower())
    {
        board[row][col].set_flower(false);
        board[row][col].set_flower_bear(true);
        board[row][col].set_identifier('P');
    }
    else if(board[row][col].get_empty())
    {
        board[row][col].set_empty(false);
        board[row][col].set_bear(true);
        board[row][col].set_identifier('B');
    }
    board[row][col].set_animal(Living_Being_Factory::create_being('b'));
}

void rabbit_eats(Square **board, Ordered_Pair dest, Rabbit *r)
{
    // get the number of calories that we can eat
    int max_to_eat = r->get_max_calories()-r->get_curr_calories();
    int curr_eat = 5;

    // find out what we're eating
    bool grass = true;
    if (board[dest.row][dest.col].get_flower_rabbit())
    {
        grass = false;
    }

    // next, let's eat grass
    if (grass)
    {
        // if the grass only has <= calories per grass, then we just kill the grass
        Grass* g = (Grass*)board[dest.row][dest.col].get_plant();
        if (g->get_curr_calories() <= curr_eat)
        {
            r->eat(g->get_curr_calories());
            remove_grass(board, dest);
        }

            // else we can eat the grass, but there will still be grass left
        else
        {
            // first, get the number of calories per grass that we will eat extra
            int x = g->get_curr_calories();
            int y = r->get_calories_per_20_grass();
            int extra = x/y;
            curr_eat = curr_eat + extra;
            r->eat(curr_eat);
            g->set_curr_calories(g->get_curr_calories()-extra);
        }
    }
    else // we're eating flowers
    {
        // if the grass only has <= calories per grass, then we just kill the grass
        Flower* f = (Flower*)board[dest.row][dest.col].get_plant();
        int c = f->get_curr_calories();
        int m = max_to_eat;
        if (f->get_curr_calories() <= curr_eat)
        {
            r->eat(f->get_curr_calories());
            remove_flower(board, dest);
        }

            // else we can eat the grass, but there will still be grass left
        else
        {
            // first, get the number of calories per grass that we will eat extra
            int x = f->get_curr_calories();
            int y = r->get_calories_per_30_flowers();
            int extra = x/y;
            curr_eat = curr_eat + extra;
            r->eat(curr_eat);
            f->set_curr_calories(f->get_curr_calories()-extra);
        }
    }
}

void deer_eats(Square **board, Ordered_Pair dest, Deer *d)
{
    int max_to_eat = d->get_max_calories()-d->get_curr_calories();
    int curr_eat = 5;
    bool grass = true;
    if (board[dest.row][dest.col].get_flower_deer())
    {
        grass = false;
    }
    if (grass)
    {
        // if the grass only has <= calories per grass, then we just kill the grass
        Grass* g = (Grass*)board[dest.row][dest.col].get_plant();
        if (g->get_curr_calories() <= curr_eat)
        {
            d->eat(g->get_curr_calories());
            remove_grass(board, dest);
        }

            // else we can eat the grass, but there will still be grass left
        else
        {
            // first, get the number of calories per grass that we will eat extra
            int x = g->get_curr_calories();
            int y = d->get_calories_per_30_grass();
            int extra = x/y;
            curr_eat = curr_eat + extra;
            d->eat(curr_eat);
            g->set_curr_calories(g->get_curr_calories()-extra);
        }
    }
    else // we're eating flowers
    {
        // if the grass only has <= calories per grass, then we just kill the grass
        Flower* f = (Flower*)board[dest.row][dest.col].get_animal();
        if (f->get_curr_calories() <= curr_eat)
        {
            d->eat(f->get_curr_calories());
            remove_flower(board, dest);
        }

            // else we can eat the grass, but there will still be grass left
        else
        {
            // first, get the number of calories per grass that we will eat extra
            int x = f->get_curr_calories();
            int y = d->get_calories_per_40_flowers();
            int extra = x/y;
            curr_eat = curr_eat + extra;
            d->eat(curr_eat);
            f->set_curr_calories(f->get_curr_calories()-extra);
        }
    }
}

void wolf_eat(Square **board, Ordered_Pair dest, Wolf *w)
{
    // first, get the poor animal that's gonna get eaten
    if (board[dest.row][dest.col].get_rabbit()       ||
        board[dest.row][dest.col].get_grass_rabbit() ||
        board[dest.row][dest.col].get_flower_rabbit())
    {
        Rabbit* r = (Rabbit*)board[dest.row][dest.col].get_animal();

        // next, determine if the animal has enough calories to feed the max
        // amount that the wolf can take.  If not, take what the animal has
        // and kill it.
        if (r->get_curr_calories() < w->get_calories_per_rabbit())
        {
            w->eat(r->get_curr_calories());
        }
        else // we eat what we can and leave the rest.... TO ROT
        {
            w->eat(w->get_calories_per_rabbit());
        }
    }
    else
    {
        Deer* d = (Deer*)board[dest.row][dest.col].get_animal();
        if (d->get_curr_calories() < w->get_calories_per_rabbit())
        {
            w->eat(d->get_curr_calories());
        }
        else // we eat what we can and leave the rest.... TO ROT
        {
            w->eat(w->get_calories_per_deer());
        }
    }
    // finally, set the animal in the square as the wolf
    board[dest.row][dest.col].set_animal(w);
}

void bear_eat(Square **board, Ordered_Pair dest, Bear *b)
{
    if (board[dest.row][dest.col].get_rabbit()       ||
        board[dest.row][dest.col].get_grass_rabbit() ||
        board[dest.row][dest.col].get_flower_rabbit())
    {
        Rabbit* r = (Rabbit*)board[dest.row][dest.col].get_animal();
        if (r->get_curr_calories() < b->get_calories_per_rabbit())
        {
            b->eat(r->get_curr_calories());
        }
        else // we eat what we can and leave the rest.... TO ROT
        {
            b->eat(b->get_calories_per_rabbit());
        }
    }
    else
    {
        Deer* d = (Deer*)board[dest.row][dest.col].get_animal();
        if (d->get_curr_calories() < b->get_calories_per_rabbit())
        {
            b->eat(d->get_curr_calories());
        }
        else // we eat what we can and leave the rest.... TO ROT
        {
            b->eat(b->get_calories_per_deer());
        }
    }
    // finally, set the animal in the square as the wolf
    board[dest.row][dest.col].set_animal(b);
}

void remove_flower(Square **board, Ordered_Pair dest)
{
    board[dest.row][dest.col].set_plant(0);
    board[dest.row][dest.col].set_flower_rabbit(false);
    board[dest.row][dest.col].set_rabbit(true);
    board[dest.row][dest.col].set_identifier('r');
}

void remove_grass(Square **board, Ordered_Pair dest)
{
    board[dest.row][dest.col].set_plant(0);
    board[dest.row][dest.col].set_grass_rabbit(false);
    board[dest.row][dest.col].set_rabbit(true);
    board[dest.row][dest.col].set_identifier('r');
}

bool there_is_neighboring_predator(Square **board, Ordered_Pair dest, Ordered_Pair predator, char& direction)
{
    bool is_predator = false;
    // look left
    if (dest.col-1 >= 0)
    {
        if (board[dest.row][dest.col-1].get_wolf()        ||
            board[dest.row][dest.col-1].get_bear()        ||
            board[dest.row][dest.col-1].get_grass_wolf()  ||
            board[dest.row][dest.col-1].get_grass_bear()  ||
            board[dest.row][dest.col-1].get_flower_wolf() ||
            board[dest.row][dest.col-1].get_flower_bear())
        {
            predator.row = dest.row;
            predator.col = dest.col-1;
            direction = 'l';
            is_predator = true;
        }
    }

    // look up
    if (dest.row-1 >= 0)
    {
        if (board[dest.row-1][dest.col].get_wolf()        ||
            board[dest.row-1][dest.col].get_bear()        ||
            board[dest.row-1][dest.col].get_grass_wolf()  ||
            board[dest.row-1][dest.col].get_grass_bear()  ||
            board[dest.row-1][dest.col].get_flower_wolf() ||
            board[dest.row-1][dest.col].get_flower_bear())
        {
            predator.row = dest.row-1;
            predator.col = dest.col;
            direction = 'u';
            is_predator = true;
        }
    }

        // look right
    else if (dest.col+1 < NUMCOLS)
    {
        if (board[dest.row][dest.col+1].get_wolf()        ||
            board[dest.row][dest.col+1].get_bear()        ||
            board[dest.row][dest.col+1].get_grass_wolf()  ||
            board[dest.row][dest.col+1].get_grass_bear()  ||
            board[dest.row][dest.col+1].get_flower_wolf() ||
            board[dest.row][dest.col+1].get_flower_bear())
        {
            predator.row = dest.row;
            predator.col = dest.col+1;
            direction = 'r';
            is_predator = true;
        }
    }

    // look down
    if (dest.row+1 < NUMROWS)
    {
        if (board[dest.row+1][dest.col].get_wolf()        ||
            board[dest.row+1][dest.col].get_bear()        ||
            board[dest.row+1][dest.col].get_grass_wolf()  ||
            board[dest.row+1][dest.col].get_grass_bear()  ||
            board[dest.row+1][dest.col].get_flower_wolf() ||
            board[dest.row+1][dest.col].get_flower_bear())
        {
            predator.row = dest.row+1;
            predator.col = dest.col;
            direction = 'd';
            is_predator = true;
        }
    }
    return is_predator;
}

void move_rabbit_to_new_square(Square **board, Ordered_Pair dest, Rabbit *r)
{
    if (board[dest.row][dest.col].get_flower())
    {
        board[dest.row][dest.col].set_flower(false);
        board[dest.row][dest.col].set_flower_rabbit(true);
        board[dest.row][dest.col].set_identifier('F');
    }
    else if (board[dest.row][dest.col].get_grass())
    {
        board[dest.row][dest.col].set_grass(false);
        board[dest.row][dest.col].set_grass_rabbit(true);
        board[dest.row][dest.col].set_identifier('R');
    }
    else
    {
        cout << "FAILED SANITY CHECK in add_rabbit_to_new_square()." << endl;
        cout << "Conditions for new square should only contain flower or grass." << endl;
        cout << "Exiting program." << endl;
        exit(EXIT_FAILURE);
    }
    board[dest.row][dest.col].set_animal(r);
}

void move_wolf_to_new_square(Square **board, Ordered_Pair dest, Wolf *w)
{
    if (board[dest.row][dest.col].get_rabbit())
    {
        board[dest.row][dest.col].set_rabbit(false);
        board[dest.row][dest.col].set_wolf(true);
        board[dest.row][dest.col].set_identifier('W');
    }
    else if (board[dest.row][dest.col].get_deer())
    {
        board[dest.row][dest.col].set_deer(false);
        board[dest.row][dest.col].set_wolf(true);
        board[dest.row][dest.col].set_identifier('W');
    }
    else if(board[dest.row][dest.col].get_grass_rabbit() ||
            board[dest.row][dest.col].get_grass_deer())
    {
        board[dest.row][dest.col].set_grass_rabbit(false);
        board[dest.row][dest.col].set_grass_wolf(true);
        board[dest.row][dest.col].set_identifier('V');
    }

    else if (board[dest.row][dest.col].get_flower_rabbit() ||
             board[dest.row][dest.col].get_flower_deer())
    {
        board[dest.row][dest.col].set_flower_rabbit(false);
        board[dest.row][dest.col].set_flower_wolf(true);
        board[dest.row][dest.col].set_identifier('G');
    }
    else
    {
        cout << "FAILED SANITY CHECK in add_wolf_to_new_square()." << endl;
        cout << "Conditions for new square should only contain:" << endl;
        cout << "rabbit, deer, grass/rabbit, grass/deer, flower/rabbit, flower/deer" << endl;
        cout << "Exiting program." << endl;
        exit(EXIT_FAILURE);
    }
    board[dest.row][dest.col].set_animal(w);
}

void move_bear_to_new_square(Square **board, Ordered_Pair dest, Bear *b)
{
    if (board[dest.row][dest.col].get_rabbit())
    {
        board[dest.row][dest.col].set_rabbit(false);
        board[dest.row][dest.col].set_bear(true);
        board[dest.row][dest.col].set_identifier('B');
    }
    else if (board[dest.row][dest.col].get_deer())
    {
        board[dest.row][dest.col].set_deer(false);
        board[dest.row][dest.col].set_bear(true);
        board[dest.row][dest.col].set_identifier('B');
    }
    else if(board[dest.row][dest.col].get_grass_rabbit() ||
            board[dest.row][dest.col].get_grass_deer())
    {
        board[dest.row][dest.col].set_grass_rabbit(false);
        board[dest.row][dest.col].set_grass_bear(true);
        board[dest.row][dest.col].set_identifier('Y');
    }

    else if (board[dest.row][dest.col].get_flower_rabbit() ||
             board[dest.row][dest.col].get_flower_deer())
    {
        board[dest.row][dest.col].set_flower_rabbit(false);
        board[dest.row][dest.col].set_flower_wolf(true);
        board[dest.row][dest.col].set_identifier('V');
    }
    else
    {
        cout << "FAILED SANITY CHECK in add_wolf_to_new_square()." << endl;
        cout << "Conditions for new square should only contain:" << endl;
        cout << "rabbit, deer, grass/rabbit, grass/deer, flower/rabbit, flower/deer" << endl;
        cout << "Exiting program." << endl;
        exit(EXIT_FAILURE);
    }
    board[dest.row][dest.col].set_animal(b);
}

void move_deer_to_square(Square **board, Ordered_Pair dest, Deer *d)
{
    if (board[dest.row][dest.col].get_flower())
    {
        board[dest.row][dest.col].set_flower(false);
        board[dest.row][dest.col].set_flower_deer(true);
        board[dest.row][dest.col].set_identifier('E');
    }
    else if (board[dest.row][dest.col].get_grass())
    {
        board[dest.row][dest.col].set_grass(false);
        board[dest.row][dest.col].set_grass_deer(true);
        board[dest.row][dest.col].set_identifier('D');
    }
    else
    {
        cout << "FAILED SANITY CHECK in add_rabbit_to_new_square()." << endl;
        cout << "Conditions for new square should only contain flower or grass." << endl;
        cout << "Exiting program." << endl;
        exit(EXIT_FAILURE);
    }
    board[dest.row][dest.col].set_animal(d);
}

bool determine_if_rabbit_will_reproduce(Rabbit *r)
{
    if (r->get_curr_calories() >= r->get_min_age_to_reproduce() &&
        r->get_curr_age() >= r->get_min_age_to_reproduce())
    {
        if (rand()%100+1 == r->get_reproductive_rate())
        {
            return true; // 50% chance of reproduction
        }
    }
    return false;
}

bool determine_if_deer_will_reproduce(Deer *d)
{
    if (d->get_curr_calories() >= d->get_min_age_to_reproduce() &&
        d->get_curr_age() >= d->get_min_age_to_reproduce())
    {
        if (rand()%100+1 < d->get_reproductive_rate())
        {
            return true; // 40% chance of reproduction
        }
    }
    return false;
}

bool determine_if_wolf_will_reproduce(Wolf *w)
{
    if (w->get_curr_calories() >= w->get_min_age_to_reproduce() &&
        w->get_curr_age() >= w->get_min_age_to_reproduce())
    {
        if (rand()%100+1 < w->get_reproductive_rate())
        {
            return true; // 40% chance of reproduction
        }
    }
    return false;
}

bool determine_if_bear_will_reproduce(Bear *b)
{
    if (b->get_curr_calories() >= b->get_min_age_to_reproduce() &&
        b->get_curr_age() >= b->get_min_age_to_reproduce())
    {
        if (rand()%100+1 < b->get_reproductive_rate())
        {
            return true; // 40% chance of reproduction
        }
    }
    return false;
}

Ordered_Pair get_neighbor_with_highest_caloric_yield(Square **board, vector<Ordered_Pair> &neighbors)
{
    Ordered_Pair best_neighbor;
    best_neighbor.row = -999;
    best_neighbor.col = 0;
    int calories = 0;
    // go through each square and get the plant with the highest yield
    for (int i = 0; i < neighbors.size(); i++)
    {
        if(board[neighbors[i].row][neighbors[i].col].get_grass())
        {
            Grass* g = (Grass*)board[neighbors[i].row][neighbors[i].col].get_plant();
            if (g->get_curr_calories() > calories)
            {
                best_neighbor.row = neighbors[i].row;
                best_neighbor.col = neighbors[i].col;
                calories = g->get_curr_calories();
            }
        }
        else if (board[neighbors[i].row][neighbors[i].col].get_flower())
        {
            Flower* f = (Flower*)board[neighbors[i].row][neighbors[i].col].get_plant();
            if (f->get_curr_calories() > calories)
            {
                best_neighbor.row = neighbors[i].row;
                best_neighbor.col = neighbors[i].col;
                calories = f->get_curr_calories();
            }
        }
        else
        {
            cout << "FAILED SANITY CHECK in get_neighbor_with_highest_caloric_yield()." << endl;
            cout << "All neighbors should have been vetted as flowers or grass only." << endl;
            cout << "Exiting program." << endl;
            exit(EXIT_FAILURE);
        }
    }
    return best_neighbor;
}

vector<Ordered_Pair> get_neighbors_that_have_only_plants(Square **board, int row, int col)
{
    vector<Ordered_Pair> neighbors;

    // look up
    if (row-1 >= 0)
    {
        if (board[row-1][col].get_grass() || board[row-1][col].get_flower())
        {
            Ordered_Pair above;
            above.row = row-1;
            above.col = col;
            neighbors.push_back(above);
        }
    }

    // look down
    if (row+1 < NUMROWS)
    {
        if (board[row+1][col].get_grass() || board[row+1][col].get_flower())
        {
            Ordered_Pair below;
            below.row = row+1;
            below.col = col;
            neighbors.push_back(below);
        }
    }

    // look left
    if (col-1 >= 0)
    {
        if (board[row][col-1].get_grass() || board[row][col-1].get_flower())
        {
            Ordered_Pair left;
            left.row = row;
            left.col = col-1;
            neighbors.push_back(left);
        }
    }

    // look right
    if (col+1 < NUMCOLS)
    {
        if (board[row][col+1].get_grass() || board[row][col+1].get_flower())
        {
            Ordered_Pair right;
            right.row = row;
            right.col = col+1;
            neighbors.push_back(right);
        }
    }
    return neighbors;
}

vector<Ordered_Pair> get_neighbors_that_have_only_prey(Square **board, int row, int col)
{
    vector<Ordered_Pair> neighbors;
    // look up
    if (row-1 >= 0)
    {
        if (board[row-1][col].get_rabbit()        ||
            board[row-1][col].get_grass_rabbit()  ||
            board[row-1][col].get_deer()          ||
            board[row-1][col].get_grass_deer()    ||
            board[row-1][col].get_flower_rabbit() ||
            board[row-1][col].get_flower_deer())
        {
            Ordered_Pair above;
            above.row = row-1;
            above.col = col;
            neighbors.push_back(above);
        }
    }

    // look down
    if (row+1 < NUMROWS)
    {
        if (board[row+1][col].get_rabbit()        ||
            board[row+1][col].get_grass_rabbit()  ||
            board[row+1][col].get_deer()          ||
            board[row+1][col].get_grass_deer()    ||
            board[row+1][col].get_flower_rabbit() ||
            board[row+1][col].get_flower_deer())
        {
            Ordered_Pair below;
            below.row = row+1;
            below.col = col;
            neighbors.push_back(below);
        }
    }

    // look left
    if (col-1 >= 0)
    {
        if (board[row][col-1].get_rabbit()        ||
            board[row][col-1].get_grass_rabbit()  ||
            board[row][col-1].get_deer()          ||
            board[row][col-1].get_grass_deer()    ||
            board[row][col-1].get_flower_rabbit() ||
            board[row][col-1].get_flower_deer())
        {
            Ordered_Pair left;
            left.row = row;
            left.col = col-1;
            neighbors.push_back(left);
        }
    }

    // look right
    if (col+1 < NUMCOLS)
    {
        if (board[row][col+1].get_rabbit()        ||
            board[row][col+1].get_grass_rabbit()  ||
            board[row][col+1].get_deer()          ||
            board[row][col+1].get_grass_deer()    ||
            board[row][col+1].get_flower_rabbit() ||
            board[row][col+1].get_flower_deer())
        {
            Ordered_Pair right;
            right.row = row;
            right.col = col+1;
            neighbors.push_back(right);
        }
    }
    return neighbors;
}

void remove_animal_from_square(Square **board, int row, int col, string animal_type)
{
    // remove the animal entirely
    board[row][col].set_animal(0);

    if (board[row][col].get_rabbit())
    {
        board[row][col].set_rabbit(false);
        board[row][col].set_empty(true);
        board[row][col].set_identifier(' '); // set to empty
    }
    else if(board[row][col].get_deer())
    {
        board[row][col].set_deer(false);
        board[row][col].set_empty(true);
        board[row][col].set_identifier(' '); // set to empty
    }
    else if (board[row][col].get_wolf())
    {
        board[row][col].set_wolf(false);
        board[row][col].set_empty(true);
        board[row][col].set_identifier(' '); // set to empty
    }
    else if(board[row][col].get_bear())
    {
        board[row][col].set_bear(false);
        board[row][col].set_empty(true);
        board[row][col].set_identifier(' '); // set to empty
    }
    else if (board[row][col].get_grass_rabbit())
    {
        board[row][col].set_grass_rabbit(false);
        board[row][col].set_grass(true);
        board[row][col].set_identifier('_'); // set to grass
    }
    else if (board[row][col].get_flower_rabbit())
    {
        board[row][col].set_flower(true);
        board[row][col].set_flower_rabbit(false);
        board[row][col].set_identifier('i'); // set to flower
    }
    else if (board[row][col].get_grass_deer())
    {
        board[row][col].set_grass_deer(false);
        board[row][col].set_grass(true);
        board[row][col].set_identifier('_'); // set to grass
    }
    else if(board[row][col].get_flower_deer())
    {
        board[row][col].set_flower(true);
        board[row][col].set_flower_deer(false);
        board[row][col].set_identifier('i'); // set to flower
    }
    else if (board[row][col].get_grass_wolf())
    {
        board[row][col].set_grass_wolf(false);
        board[row][col].set_grass(true);
        board[row][col].set_identifier('_'); // set to grass
    }
    else if (board[row][col].get_flower_wolf())
    {
        board[row][col].set_flower(true);
        board[row][col].set_flower_wolf(false);
        board[row][col].set_identifier('i'); // set to flower
    }
    else if (board[row][col].get_grass_bear())
    {
        board[row][col].set_grass_bear(false);
        board[row][col].set_grass(true);
        board[row][col].set_identifier('_'); // set to grass
    }
    else if (board[row][col].get_flower_bear())
    {
        board[row][col].set_flower(true);
        board[row][col].set_flower_bear(false);
        board[row][col].set_identifier('i'); // set to flower
    }
    else
    {
        remove_being_from_square_sanity_check_fail(animal_type);
    }
}

void remove_being_from_square_sanity_check_fail(string being)
{
    cout << "FAILED SANITY CHECK in remove_" << being << "_from_square()." << endl;
    cout << "Conditions were not met." << endl;
    exit(EXIT_FAILURE);
}

void flower_turn(Square **board, int row, int col)
{
    Flower* f = (Flower*) board[row][col].get_plant();
    f->eat(2);
    board[row][col].set_plant(f);
}

void grass_turn(Square **board, int row, int col)
{
    Grass* g = (Grass*)board[row][col].get_plant();
    g->eat(1);
    board[row][col].set_plant(g);
}

int get_num_turns()
{
    int num_turns = 0;
    cout << "How many turns would you like the program to take?" << endl;
    cout << "-> ";
    cin >> num_turns;
    return num_turns;
}

void print_random_arrays(Ordered_Pair *grass, Ordered_Pair *flower, Ordered_Pair *rabbit, Ordered_Pair *deer,
                         Ordered_Pair *wolf, Ordered_Pair *bear)
{
    cout << "Starting grass coordinates:" << endl;
    print_array(grass, NUMGRASS);
    cout << "Starting flower coordinates:" << endl;
    print_array(flower, NUMFLOWERS);
    cout << "Starting rabbit coordinates" << endl;
    print_array(rabbit, NUMRABBITS);
    cout << "Starting deer coordinates:" << endl;
    print_array(deer, NUMDEER);
    cout << "Starting wolf coordinates:" << endl;
    print_array(wolf, NUMWOLVES);
    cout << "Starting bear coordinates:" << endl;
    print_array(bear, NUMBEAR);
    cout << endl;
}

void print_array(Ordered_Pair *being, int num_beings)
{
    for (int i = 0; i < num_beings; i++)
    {
        cout << "\t(" << i+1 << ")\t" << being[i].row << ",\t" << being[i].col << endl;
    }
    cout << endl;
}

void print_board(Square **board)
{
    cout << "\t\t\t";
    int j = 0;
    for (int i = 0; i < NUMCOLS; i++)
    {
        cout << j++ << " ";
        if (j == 10) j = 0;
    }
    cout << endl;
    for (int row = 0; row < NUMROWS; row++)
    {
        cout << "\t\t" << row << "\t";
        for (int col = 0; col < NUMCOLS; col++)
        {
            cout << board[row][col].get_identifier() << " ";
        }
        cout << endl;
    }
}

void insert_beings_into_board(Square      **board,
                              Ordered_Pair *grass,
                              Ordered_Pair *flower,
                              Ordered_Pair *rabbit,
                              Ordered_Pair *deer,
                              Ordered_Pair *wolf,
                              Ordered_Pair *bear)
{
    // insert the plants
    for (int row = 0; row < NUMROWS; row++)
    {
        for (int col = 0; col < NUMCOLS; col++)
        {
            if (should_insert(board, grass, row, col, NUMGRASS))
            {
                insert_grass(board, row, col);
            }
            if (should_insert(board, flower, row, col, NUMFLOWERS))
            {
                insert_flower(board, row, col);
            }
        }
    }

    // then insert the animals
    for (int row = 0; row < NUMROWS; row++)
    {
        for (int col = 0; col < NUMCOLS; col++)
        {
            // check to insert rabbit
            if (should_insert(board, rabbit, row, col, NUMRABBITS))
            {
                insert_rabbit(board, row, col);
            }

            // check to insert deer
            if (should_insert(board, deer, row, col, NUMDEER))
            {
                insert_deer(board, row, col);
            }

            // check to insert wolf
            if (should_insert(board, wolf, row, col, NUMWOLVES))
            {
                insert_wolf(board, row, col);
            }

            // check to insert bear
            if (should_insert(board, bear, row, col, NUMBEAR))
            {
                insert_bear(board, row, col);
            }
        }
    }

    cout << "After inserting everything into the board... is (0,0) have a piece?" << endl;
    print_board(board);

    // insert a grass into (0,0) to fix a weird bug
    //insert_grass(board, 0,0);
    //insert_rabbit(board, 0,0);
}

void insert_bear(Square **board, int row, int col)
{
    board[row][col].set_animal(Living_Being_Factory::create_being('w'));
    if (board[row][col].get_grass())
    {
        board[row][col].set_grass(false);
        board[row][col].set_bear(false);
        board[row][col].set_grass_bear(true);
        board[row][col].set_identifier('Y');
    }
    else if (board[row][col].get_flower())
    {
        board[row][col].set_flower(false);
        board[row][col].set_flower_bear(true);
        board[row][col].set_identifier('P');
    }
    else
    {
        failed_insert_sanity_check("wolf");
    }
}

void insert_wolf(Square **board, int row, int col)
{
    board[row][col].set_animal(Living_Being_Factory::create_being('w'));
    if (board[row][col].get_grass())
    {
        board[row][col].set_grass(false);
        board[row][col].set_wolf(false);
        board[row][col].set_grass_wolf(true);
        board[row][col].set_identifier('V');
    }
    else if (board[row][col].get_flower())
    {
        board[row][col].set_flower(false);
        board[row][col].set_wolf(false);
        board[row][col].set_flower_wolf(true);
        board[row][col].set_identifier('G');
    }
    else
    {
        failed_insert_sanity_check("wolf");
    }
}

void insert_deer(Square **board, int row, int col)
{
    board[row][col].set_animal(Living_Being_Factory::create_being('d'));
    if (board[row][col].get_grass())
    {
        board[row][col].set_grass(false);
        board[row][col].set_deer(false);
        board[row][col].set_grass_deer(true);
        board[row][col].set_identifier('D');
    }
    else if (board[row][col].get_flower())
    {
        board[row][col].set_flower(false);
        board[row][col].set_deer(false);
        board[row][col].set_flower_deer(true);
        board[row][col].set_identifier('E');
    }
    else
    {
        failed_insert_sanity_check("deer");
    }
}

void insert_rabbit(Square **board, int row, int col)
{
    board[row][col].set_animal(Living_Being_Factory::create_being('r'));
    if (board[row][col].get_grass())
    {
        board[row][col].set_grass(false);
        board[row][col].set_rabbit(false);
        board[row][col].set_grass_rabbit(true);
        board[row][col].set_identifier('R');
    }
    else if (board[row][col].get_flower())
    {
        board[row][col].set_flower(false);
        board[row][col].set_rabbit(false);
        board[row][col].set_flower_rabbit(true);
        board[row][col].set_identifier('F');
    }
    else
    {
        failed_insert_sanity_check("rabbit");
    }
}

void failed_insert_sanity_check(string animal)
{
    cout << "Failed sanity check in insert." << endl;
    cout << "Conditions were not correct with insert " << animal << "." << endl;
    exit(EXIT_FAILURE);
}

void insert_flower(Square **board, int row, int col)
{
    board[row][col].set_plant(Living_Being_Factory::create_being('f'));
    board[row][col].set_empty(false);
    board[row][col].set_flower(true);
    board[row][col].set_identifier('i');
}

void insert_grass(Square **board, int row, int col)
{
    board[row][col].set_plant(Living_Being_Factory::create_being('g'));
    board[row][col].set_empty(false);
    board[row][col].set_grass(true);
    board[row][col].set_identifier('_');
}

bool should_insert(Square **board, Ordered_Pair *being, int row, int col, int number_of_beings)
{
    for (int i = 0; i < number_of_beings; i++)
    {
        if (being[i].row == row && being[i].col == col)
        {
            return true;
        }
    }
    return false;
}

Ordered_Pair *create_bear_array(Ordered_Pair *rabbit, Ordered_Pair *deer, Ordered_Pair *wolf) {
    Ordered_Pair* bear = new Ordered_Pair[NUMBEAR];
    for (int i = 0; i < NUMBEAR; i++)
    {
        int row = rand()%NUMROWS;
        int col = rand()%NUMCOLS;
        bool is_unique_pair = true;
        bool is_not_in_rabbit_array = true;
        bool is_not_in_deer_array = true;
        bool is_not_in_wolf_array = true;
        for (int j = 0; j < NUMBEAR; j++)
        {
            if (bear[j].col == col && bear[j].row == row)
            {
                is_unique_pair = false;
                break;
            }
        }
        for (int k = 0; k < NUMRABBITS; k++)
        {
            if (rabbit[k].col == col && rabbit[k].row == row)
            {
                is_not_in_rabbit_array = false;
                break;
            }
        }
        for (int l = 0; l < NUMDEER; l++)
        {
            if (deer[l].col == col && deer[l].row == row)
            {
                is_not_in_deer_array = false;
                break;
            }
        }
        for (int m = 0; m < NUMWOLVES; m++)
        {
            if (deer[m].col == col && deer[m].row == row)
            {
                is_not_in_wolf_array = false;
                break;
            }
        }
        if (is_unique_pair && is_not_in_rabbit_array &&
            is_not_in_deer_array && is_not_in_wolf_array)

        {
            bear[i].row = row;
            bear[i].col = col;
        }
        else i--;
    }
    return bear;
}

Ordered_Pair *create_wolf_array(Ordered_Pair *rabbit, Ordered_Pair *deer)
{
    Ordered_Pair* wolf = new Ordered_Pair[NUMWOLVES];
    for (int i = 0; i < NUMWOLVES; i++)
    {
        int row = rand()%NUMROWS;
        int col = rand()%NUMCOLS;
        bool is_unique_pair = true;
        bool is_not_in_rabbit_array = true;
        bool is_not_in_deer_array = true;
        for (int j = 0; j < NUMWOLVES; j++)
        {
            if (wolf[j].col == col && wolf[j].row == row)
            {
                is_unique_pair = false;
                break;
            }
        }
        for (int k = 0; k < NUMRABBITS; k++)
        {
            if (rabbit[k].col == col && rabbit[k].row == row)
            {
                is_not_in_rabbit_array = false;
                break;
            }
        }
        for (int l = 0; l < NUMDEER; l++)
        {
            if (deer[l].col == col && deer[l].row == row)
            {
                is_not_in_deer_array = false;
                break;
            }
        }
        if (is_unique_pair && is_not_in_rabbit_array && is_not_in_deer_array)
        {
            wolf[i].row = row;
            wolf[i].col = col;
        }
        else i--;
    }
    return wolf;
}

Ordered_Pair *create_deer_array(Ordered_Pair *rabbit)
{
    Ordered_Pair* deer = new Ordered_Pair[NUMDEER];
    for (int i = 0; i < NUMDEER; i++)
    {
        int row = rand()%NUMROWS;
        int col = rand()%NUMCOLS;
        bool is_unique_pair = true;
        bool is_not_in_rabbit_array = true;
        for (int j = 0; j < NUMDEER; j++)
        {
            if (deer[j].col == col && deer[j].row == row)
            {
                is_unique_pair = false;
                break;
            }
        }
        for (int k = 0; k < NUMRABBITS; k++)
        {
            if (rabbit[k].col == col && rabbit[k].row == row)
            {
                is_not_in_rabbit_array = false;
                break;
            }
        }
        if (is_unique_pair && is_not_in_rabbit_array)
        {
            deer[i].row = row;
            deer[i].col = col;
        }
        else i--;
    }
    return deer;
}

Ordered_Pair *create_rabbit_array()
{
    Ordered_Pair* rabbit = new Ordered_Pair[NUMRABBITS];
    for (int i = 0; i < NUMRABBITS; i++)
    {
        int row = rand()%NUMROWS;
        int col = rand()%NUMCOLS;
        bool is_unique_pair = true;
        for (int j = 0; j < NUMRABBITS; j++)
        {
            if (rabbit[j].col == col && rabbit[j].row == row)
            {
                is_unique_pair = false;
                i--;
                break;
            }
        }
        if (is_unique_pair)
        {
            rabbit[i].row = row;
            rabbit[i].col = col;
        }
    }
    return rabbit;
}

Ordered_Pair *create_flower_array(Ordered_Pair *grass)
{
    Ordered_Pair* flower = new Ordered_Pair[NUMFLOWERS];
    for (int i = 0; i < NUMFLOWERS; i++)
    {
        int row = rand()%NUMROWS;
        int col = rand()%NUMCOLS;
        bool is_unique_pair = true;
        bool is_not_int_grass_array = true;
        for (int j = 0; j < NUMFLOWERS; j++)
        {
            if (flower[j].col == col && flower[j].row == row)
            {
                is_unique_pair = false;
                break;
            }
        }
        for (int k = 0; k < NUMGRASS; k++)
        {
            if (grass[k].col == col && grass[k].row == row)
            {
                is_not_int_grass_array = false;
                break;
            }
        }
        if (is_unique_pair && is_not_int_grass_array)
        {
            flower[i].row = row;
            flower[i].col = col;
        }
        else i--;
    }
    return flower;
}

Ordered_Pair *create_grass_array()
{
    Ordered_Pair* grass = new Ordered_Pair[NUMGRASS];
    for (int i = 0; i < NUMGRASS; i++)
    {
        int row = rand()%NUMROWS;
        int col = rand()%NUMCOLS;
        bool is_unique_pair = true;
        for (int j = 0; j < NUMGRASS; j++)
        {
            if (grass[j].col == col && grass[j].row == row)
            {
                is_unique_pair = false;
                i--;
                break;
            }
        }
        if (is_unique_pair)
        {
            grass[i].row = row;
            grass[i].col = col;
        }
    }
    return grass;
}

Square **initialize_board()
{
    Square** board = new Square*[NUMROWS];
    for (int row = 0; row < NUMROWS; row++)
        board[row] = new Square[NUMCOLS];

    for (int row = 0; row < NUMROWS; row++)
    {
        for (int col = 0; col < NUMCOLS; col++)
        {
            board[row][col].set_identifier(' ');
            board[row][col].set_animal(0);
            board[row][col].set_plant(0);
            board[row][col].set_empty(true);
            board[row][col].set_grass(false);
            board[row][col].set_flower(false);
            board[row][col].set_rabbit(false);
            board[row][col].set_deer(false);
            board[row][col].set_wolf(false);
            board[row][col].set_bear(false);
            board[row][col].set_grass_rabbit(false);
            board[row][col].set_grass_deer(false);
            board[row][col].set_grass_wolf(false);
            board[row][col].set_grass_bear(false);
            board[row][col].set_flower_rabbit(false);
            board[row][col].set_flower_deer(false);
            board[row][col].set_flower_wolf(false);
            board[row][col].set_flower_bear(false);
        }
    }
    return board;
}

void print_value_of_square(Square **board, int row, int col)
{
    if (board[row][col].get_rabbit())        cout << "\t" << row << "," << col << " is rabbit()" << endl;
    if (board[row][col].get_grass_rabbit())  cout << "\t" << row << "," << col << " is grass/rabbit()" << endl;
    if (board[row][col].get_flower_rabbit()) cout << "\t" << row << "," << col << " is flower/rabbit()" << endl;
    if (board[row][col].get_deer())          cout << "\t" << row << "," << col << " is deer()" << endl;
    if (board[row][col].get_grass_deer())    cout << "\t" << row << "," << col << " is grass/deer()" << endl;
    if (board[row][col].get_flower_deer())   cout << "\t" << row << "," << col << " is flower/deer()" << endl;
    if (board[row][col].get_wolf())          cout << "\t" << row << "," << col << " is wolf()" << endl;
    if (board[row][col].get_grass_wolf())    cout << "\t" << row << "," << col << " is grass/wolf()" << endl;
    if (board[row][col].get_flower_wolf())   cout << "\t" << row << "," << col << " is flower/wolf()" << endl;
    if (board[row][col].get_bear())          cout << "\t" << row << "," << col << " is bear()" << endl;
    if (board[row][col].get_grass_bear())    cout << "\t" << row << "," << col << " is grass/bear()" << endl;
    if (board[row][col].get_flower_bear())   cout << "\t" << row << "," << col << " is flower/bear()" << endl;
    if (board[row][col].get_grass())         cout << "\t" << row << "," << col << " is grass()" << endl;
    if (board[row][col].get_flower())        cout << "\t" << row << "," << col << " is flower()" << endl;
    if (board[row][col].get_empty())         cout << "\t" << row << "," << col << " is empty()" << endl;
}







