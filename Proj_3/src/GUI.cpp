#include "GUI.h"
#include <iostream>
#include <algorithm>
#include <time.h>
#include "Grass.h"
#include "Flower.h"

using namespace std;

GUI::GUI()
{
    app = new sf::RenderWindow(sf::VideoMode(800, 700), "SFML window");
    srand (time(NULL));
    populate_grid();
    print_ASCII('p');
}

GUI::~GUI()
{
    //dtor
}

void GUI::Run()
{
    sf::Clock deltaClock;
    while (app->isOpen())
    {
        // Process events

        sf::Event event;
        while (app->pollEvent(event))
        {
            //store mouse position
            sf::Vector2i mousePos;
            mousePos.x = sf::Mouse::getPosition(*app).x;
            mousePos.y = sf::Mouse::getPosition(*app).y;

            // Close window : exit
            if (event.type == sf::Event::Closed)
                app->close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
            // left key is pressed: move our character
                app->close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                // left mouse button is pressed: shoot
                cout << "Mouse Pressed" << endl;
                if(close->isHover(mousePos)){
                    app->close();
                }

                if(start->isHover(mousePos)){
                    cout << "Start simulation" << endl;
                }

            }

            //getting mouse position



            if(close->isHover(mousePos)){
                //cout << "Close" << endl;
                close->text.setColor(sf::Color::Yellow);
            }
            else{
                close->text.setColor(sf::Color::White);
            }

            if( start->isHover(mousePos)){
                //cout << "Close" << endl;
                start->text.setColor(sf::Color::Yellow);
            }
            else{
                start->text.setColor(sf::Color::White);
            }
        }
        cout << "timer start" << endl;
        //setting steps to follow timer routine
        sf::Time dt = deltaClock.getElapsedTime();
        timer = dt.asMilliseconds();

        if(timer > 16*20) { //need 16 for to get 60fps
            //cout << "Time:" << timer << endl;

            timer = 0;
            deltaClock.restart();

            step();
            cout << "STEP" << endl;
            //print_ASCII('a');

        }

        // Clear screen
        cout << "clear screen" << endl;
        app->clear();

        //app.draw(text);
        //app->draw(close->border);
        cout << "draw" << endl;
        app->draw(close->text);
        //app->draw(start->border);
        app->draw(start->text);
        // Update the windo
        cout << "grid" << endl;
        drawGrid();
        cout << "disp" << endl;
        //cout << "Ddraw " << endl;
        app->display();
        cout << "disp end" << endl;
    }

}

//
// go through grid, take each turn
//
void GUI::step()
{

    for (int row = 0; row < NUMROWS; row++)
    {
        for (int col = 0; col < NUMCOLS; col++)
        {
            if (grid[row][col].p_id != ' ')
            {

                grid[row][col].get_plant()->take_turn();
                cout << "plant turn end" << endl;
            }

            if (grid[row][col].a_id != ' ')
            {
                cout << "animal turn start" << endl;
                animal_turn(row, col, grid[row][col].a_id);

            }
        }
    }

    for (int row = 0; row < NUMROWS; row++)
    {
        for (int col = 0; col < NUMCOLS; col++)
        {
            if (grid[row][col].a_id == 'R')
            {
                Rabbit* r = (Rabbit*)grid[row][col].get_animal();
                r->set_move_made(false);
            }
            //
            // change other bools later
        }
    }
}

void GUI::animal_turn(int row, int col, char type)
{
    switch(type)
    {
    case('R'):
        {
            rabbit_turn(row, col);
            break;
        }
    case('D'):
        {
            //deer_turn(row, col);
            break;
        }
    case('B'):
        {
            //bear_turn(row, col);
            break;
        }
    case('W'):
        {
            //wolf_turn(row, col);
            break;
        }
    }
}

void GUI::rabbit_turn(int row, int col)
{

    // get the rabbit, see if it's turn is finished
    Rabbit* r = (Rabbit*)grid[row][col].get_animal();
    if (!r->get_move_made())
    {
       r->set_move_made(true);

       r->hunger();
       //r->age();

       if (r->get_curr_age() >= r->get_max_age() || r->get_curr_calories() == 0)
       {
           r->die();
           delete[] &r;
           grid[row][col].set_animal(NULL);
           cout << "Dead Rabbit" << endl;

           grid[row][col].a_id = ' ';
           if (grid[row][col].p_id == 'G')
           {
               grid[row][col].tile.setColor(sf::Color::Green);
           }
           else if (grid[row][col].p_id == 'F')
           {
               grid[row][col].tile.setColor(sf::Color::Yellow);
           }
           else
           {
                grid[row][col].tile.setColor(sf::Color::Black);
           }
       }
       else
       {

           vector<Ordered_Pair> neighbors = get_neighbors_that_have_only_plants(row, col);
            if (!neighbors.empty()) // else the turn ends
            {

                Ordered_Pair dest = get_neighbor_with_highest_caloric_yield(neighbors);

                // next, will we reproduce in this turn
                //bool will_reproduce_this_turn = determine_if_rabbit_will_reproduce(r);
                //if (will_reproduce) cout << "Rabbit may be born" << endl;

                // move to grid space

                grid[dest.row][dest.col].set_animal(r);
                grid[dest.row][dest.col].a_id = 'R';
                grid[dest.row][dest.col].tile.setColor(sf::Color::Magenta);


                grid[row][col].a_id = ' ';
                grid[row][col].set_animal(NULL);
                // need to set color if flower/grass
                if (grid[row][col].p_id == 'G')
                {
                    grid[row][col].tile.setColor(sf::Color::Green);
                }
                else if(grid[row][col].p_id == 'F')
                {
                    grid[row][col].tile.setColor(sf::Color::Yellow);
                }
                else{
                    grid[row][col].tile.setColor(sf::Color::Black);
                }

                //cout << "dest " << dest.row << "," << dest.col << endl;
                //cout << "target " << row << "," << col << endl;


                //
                // now that we've moved there, we check for a neighboring predator.  If there
                // is one, we flee.  If there is not, we eat, possibly reproduce, and end turn.
                //
                Ordered_Pair neighboring_predator;
                neighboring_predator.col = -999;
                neighboring_predator.row = -999;
                char direction = ' ';

               if (!there_is_neighboring_predator(dest, neighboring_predator, direction))
                {
                    if(r->get_curr_calories() < r->get_max_calories()){
                       // cout << "Rabbit cals:" << r->get_curr_calories() << endl;
                        rabbit_eats(dest, r);
                        cout << "rabbit ate" << endl;
                    }


                    //if (will_reproduce_this_turn)
                    //{
                      //  rabbit_reproduces(row, col);
                    //}
                }
                //else
                //{
                //}
            }
       }

    }

/*
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
                    rabbit_eats(board, destination, r);


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
    */
}

void GUI::rabbit_reproduces(int row, int col)
{
    // first we need to know if the baby rabbit will be created on a flower, grass, or empty
    /*
    if (grid[row][col].get_grass())
    {
        grid[row][col].set_grass(false);
        grid[row][col].set_grass_rabbit(true);
        grid[row][col].set_identifier('R');
    }
    else if (grid[row][col].get_flower())
    {
        grid[row][col].set_flower(false);
        grid[row][col].set_flower_rabbit(true);
        grid[row][col].set_identifier('F');
    }
    else if(grid[row][col].get_empty())
    {
        grid[row][col].set_empty(false);
        grid[row][col].set_rabbit(true);
        grid[row][col].set_identifier('r');
    }
    grid[row][col].set_animal(Living_Being_Factory::create_being('r'));
    */
}


void GUI::rabbit_eats(Ordered_Pair dest, Rabbit* r)
{

    // get the number of calories that we can eat
    int curr_eat = 5;

    // find out what we're eating




     if (grid[dest.row][dest.col].p_id == 'G')
     {
        cout << "g dest " << dest.col << "," << dest.row << endl;
        //if the grass only has <= calories per grass, then we just kill the grass
        Grass* g = (Grass*)grid[dest.row][dest.col].get_plant();
        r->eat(5);
        g->remove_calories(5);

     }
     else if (grid[dest.row][dest.col].p_id == 'F')
     {
        //if the grass only has <= calories per grass, then we just kill the grass
        cout << "f dest " << dest.col << "," << dest.row << endl;
        Flower* f = (Flower*)grid[dest.row][dest.col].get_plant();
        r->eat(5);
        f->get_curr_calories();
        cout << "remove call" << endl;
        f->remove_calories(5);
        cout << "remove call done" << endl;

     }



    cout << "done eating" << endl;

}


bool GUI::there_is_neighboring_predator(Ordered_Pair dest, Ordered_Pair predator, char direction)
{
    bool is_predator = false;
    // look left
    if (dest.col-1 >= 0)
    {
        if (grid[dest.row][dest.col-1].a_id == 'W' ||
            grid[dest.row][dest.col-1].a_id == 'B')
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
        if (grid[dest.row-1][dest.col].a_id == 'W' ||
            grid[dest.row-1][dest.col].a_id == 'B')
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
        if (grid[dest.row][dest.col+1].a_id == 'W' ||
            grid[dest.row][dest.col+1].a_id == 'B')
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
        if (grid[dest.row+1][dest.col].a_id == 'W' ||
            grid[dest.row+1][dest.col].a_id == 'B')
        {
            predator.row = dest.row+1;
            predator.col = dest.col;
            direction = 'd';
            is_predator = true;
        }
    }
    return is_predator;
}


bool GUI::determine_if_rabbit_will_reproduce(Rabbit* r)
{
    if (r->get_curr_calories() >= r->get_min_age_to_reproduce() &&
        r->get_curr_age() >= r->get_min_age_to_reproduce())
    {
        if (rand()%100+1 < r->get_reproductive_rate())
        {
            return true; // 50% chance of reproduction
        }
    }
    return false;
}


Ordered_Pair GUI::get_neighbor_with_highest_caloric_yield(vector<Ordered_Pair>neighbors)
{
    Ordered_Pair best_neighbor;
    best_neighbor.row = -999;
    best_neighbor.col = 0;
    int calories = 0;

    for (unsigned int i = 0; i < neighbors.size(); i++){
     cout << "Yield starts" << endl;
        if(grid[neighbors[i].row][neighbors[i].col].a_id != ' '){
            cout << "Animal detected in the pool of moves" << endl;
            cout << "Exiting program." << endl;
            exit(EXIT_FAILURE);
        }
        cout << "Yield ends" << endl;
    }
    // go through each square and get the plant with the highest yield
    for (unsigned int i = 0; i < neighbors.size(); i++)
    {
        if(grid[neighbors[i].row][neighbors[i].col].p_id == 'G')
        {
            Grass* g = (Grass*)grid[neighbors[i].row][neighbors[i].col].get_plant();
            if (g->get_curr_calories() > calories)
            {
                best_neighbor.row = neighbors[i].row;
                best_neighbor.col = neighbors[i].col;
                calories = g->get_curr_calories();
            }
            else if(g->get_curr_calories() < calories){
                    neighbors.erase(neighbors.begin() + i);
                    --i;

            }
        }
/*
        if(grid[neighbors[i].row][neighbors[i].col].a_id != ' '){
            cout << "Animal detected in the pool of moves" << endl;
            cout << "Exiting program." << endl;
            exit(EXIT_FAILURE);
        }
        */
    }

    for (unsigned int i = 0; i < neighbors.size(); i++)
    {
        if(grid[neighbors[i].row][neighbors[i].col].p_id == 'F')
        {

            Flower* f = (Flower*)grid[neighbors[i].row][neighbors[i].col].get_plant();
            if (f->get_curr_calories() > calories)
            {
                best_neighbor.row = neighbors[i].row;
                best_neighbor.col = neighbors[i].col;
                calories = f->get_curr_calories();
            }

            else if(f->get_curr_calories() < calories){
                    neighbors.erase(neighbors.begin() + i);
                    --i;

            }

        }


    }








/*
    for(unsigned int i = 0;i < neighbors.size();++i){
        int c = neighbors[i].col;
        int r = neighbors[i].row;
        cout << "[" << c << "][" << r << "]" << endl;

    }

    cout << "*******" << endl;
*/
    //choosing movement randomly
    int r = rand() % neighbors.size();
    //cout << "Random " << r << endl;
    //cout << "Pool " << neighbors.size() << endl;

    best_neighbor.row = neighbors[r].row;
    best_neighbor.col = neighbors[r].col;

    return best_neighbor;
}

vector<Ordered_Pair> GUI::get_neighbors_that_have_only_plants(int row, int col)
{
    vector<Ordered_Pair> all_moves;

    //start with right to corner to get all surrounding moves
    /*
        -1 0 1
        +-+-+-+
     -1 | | | |
        +-+-+-+
      0 | |R| |
        +-+-+-+
      1 | | | |
        +-+-+-+
    */
    for(int i = 0;i < 3;++i)
        for(int j = 0;j < 3;++j){
            Ordered_Pair p;
            p.col = i-1+col;
            p.row = j-1+row;
            all_moves.push_back(p);
        }

    //removing unwanted moves

    for(unsigned int i = 0;i < all_moves.size();++i){
        int c = all_moves[i].col;
        int r = all_moves[i].row;



        //removing spot where object resides
        if(c == col && r == row){
            //cout << "popping out center itself" << endl;
            all_moves.erase(all_moves.begin() + i);
            --i;

        }
    }
    for(unsigned int i = 0;i < all_moves.size();++i){
        int c = all_moves[i].col;
        int r = all_moves[i].row;


        //removing spot where object resides
        if(c < 0 || r < 0 || c > NUMCOLS-1 || r > NUMROWS-1)
        {
           all_moves.erase(all_moves.begin() + i);
            --i;

        }
    }
    for(unsigned int i = 0;i < all_moves.size();++i){
        int c = all_moves[i].col;
        int r = all_moves[i].row;



        //removing spot where object resides
        if( grid[r][c].a_id != ' '){
            all_moves.erase(all_moves.begin() + i);
            --i;

        }
    }



        //removing moves with other animals in
     //   if( grid[r][c].a_id != ' '){
     //       all_moves.erase(all_moves.begin() + i);
     //       decrement = true;

     //   }





    //}
/*
    for(unsigned int i = 0;i < all_moves.size();++i){
        cout << "[" << all_moves[i].col<< "][" << all_moves[i].row << "]" << endl;
    }
    cout << "*******" << endl;
    cout << "occupied by:" << endl;
    for(unsigned int i = 0;i < all_moves.size();++i){
        int c = all_moves[i].col;
        int r = all_moves[i].row;
        cout << grid[r][c].a_id << endl;
    }
*/
    return all_moves;
}





void GUI::drawGrid(){
    for(int i = 0;i < 40; ++i){
        for(int j = 0;j < 30; ++j)
        {
            app->draw(grid[j][i].tile.sprite);
        }
    }
}



void GUI::populate_grid()
{
    // populates the grass
    create_grass_and_flowers();
    Ordered_Pair* rabbit = create_rabbit_array();




    for (int i = 0; i < NUMRABBITS; i++)
    {
        if (grid[rabbit[i].row][rabbit[i].col].a_id == ' ')
        {
            Living_Being* r = new Rabbit();
            int col = rabbit[i].col;
            int row = rabbit[i].row;
            grid[row][col].a_id = 'R';

            sf::Vector2f v;
            v.x = (col * TILE_SIZE);
            v.y = (row * TILE_SIZE) + 100;

            grid[row][col].set_animal(r);

            grid[row][col].tile.setPostition(v);
            grid[row][col].tile.setColor(sf::Color::Magenta);
        }
    }
}

void GUI::create_grass_and_flowers()
{
    //Ordered_Pair* grass = new Ordered_Pair[NUMGRASS];
    vector<bool> pool(NUMCOLS*NUMROWS);
    for (int i = 0;i < NUMGRASS;++i){
        pool[i] = true;
    }


    std::random_shuffle ( pool.begin(), pool.end() );

    //for(int i = 0; )

    int counter = 0;
    for(int r = 0; r < NUMROWS;++r){
        for(int c = 0; c < NUMCOLS;++c){
            if(pool[counter]){
                Living_Being* g = new Grass();

                sf::Vector2f v;
                v.x = (c * TILE_SIZE);
                v.y = (r * TILE_SIZE) + 100;

                grid[r][c].set_plant(g);
                grid[r][c].p_id = 'G';
                grid[r][c].a_id = ' ';

                grid[r][c].tile.setPostition(v);
                grid[r][c].tile.setColor(sf::Color::Green);
            }
            else{
                Living_Being* f = new Flower();

                sf::Vector2f v;
                v.x = (c * TILE_SIZE);
                v.y = (r * TILE_SIZE) + 100;

                grid[r][c].set_plant(f);
                grid[r][c].p_id = 'F';
                grid[r][c].a_id = ' ';

                grid[r][c].tile.setPostition(v);
                grid[r][c].tile.setColor(sf::Color::Yellow);

            }
            counter++;
        }
    }



/*
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
    */
    //return grass;
}

Ordered_Pair* GUI::create_rabbit_array()
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


void GUI::print_ASCII(char type)
{
    if(type == 'p'){
        for (int i = 0; i < NUMROWS;++i){
            for(int j = 0;j < NUMCOLS;++j){
                cout << "[" << grid[i][j].p_id << "]";
            }
            cout << endl;
        }
    }else {
        for (int i = 0; i < NUMROWS;++i){
            for(int j = 0;j < NUMCOLS;++j){
                cout << "[" << grid[i][j].a_id << "]";
            }
            cout << endl;
        }
    }

    cout << endl << endl;
}
