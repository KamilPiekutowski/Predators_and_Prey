#include "GUI.h"
#include <iostream>
#include <algorithm>
#include <time.h>
#include <ctime>
#include "Grass.h"
#include "Flower.h"
#include "Deer.h"
#include "Wolf.h"
#include "Bear.h"
#include "Rabbit.h"
using namespace std;

const int mSecs = 500;

void GUI::pause(unsigned secs = 1U)
{
   clock_t wait = secs+mSecs+clock();
   while(wait > clock()) continue;
}

GUI::GUI()
{
    app = new sf::RenderWindow(sf::VideoMode(800, 700), "SFML window");
    srand (time(NULL));
    populate_grid();
    //print_ASCII('p');
}

GUI::~GUI(){}

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
                    this->isRunning = true;
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

        //setting steps to follow timer routine
        sf::Time dt = deltaClock.getElapsedTime();
        timer = dt.asMilliseconds();

        if((timer > 16*10) && this->isRunning ) { //need 16 for to get 60fps
            //cout << "Time:" << timer << endl;

            timer = 0;
            deltaClock.restart();
            //cout << "STEP" << endl;
            //print_ASCII('a');
            step();
            pause();

        }

        // Clear screen
        app->clear();

        //app.draw(text);
        //app->draw(close->border);
        app->draw(close->text);
        //app->draw(start->border);
        app->draw(start->text);
        // Update the windo
        drawGrid();
        //cout << "Ddraw " << endl;
        app->display();
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
                //cout << "plant turn end" << endl;
            }

            if (grid[row][col].a_id != ' ')
            {
                //cout << "animal turn start" << endl;
                animal_turn(row, col, grid[row][col].a_id);
            }
        }
    }

    for (int row = 0; row < NUMROWS; row++)
    {
        for (int col = 0; col < NUMCOLS; col++)
        {
            if ( grid[row][col].a_id == 'R' || grid[row][col].a_id == 'D')
            {
                Herbivore* r = (Herbivore*)grid[row][col].get_animal();
                //print_ASCII('a');
                r->set_move_made(false);
            }
            if ( grid[row][col].a_id == 'W' || grid[row][col].a_id == 'B')
            {
                Carnivore* r = (Carnivore*)grid[row][col].get_animal();
                //print_ASCII('a');
                r->set_move_made(false);
            }
        }
    }


    //
    // Display the number of animals, and end the program if
    // there are no more predators or prey
    //
    char winner = display_stats_check_for_end_of_program();
    if (winner == 'c')
    {
        cout << "The carnivores win the Darwin award!" << endl;
        //system("pause");
        exit(EXIT_SUCCESS);
    }
    else if (winner == 'h')
    {
        cout << "The herbivores win the Darwin award!" << endl;
        //system("pause");
        exit(EXIT_SUCCESS);
    }
}

char GUI::display_stats_check_for_end_of_program()
{
    int num_rabbits = 0;
    int num_deer    = 0;
    int num_wolves  = 0;
    int num_bear    = 0;

    for (int row = 0; row < NUMROWS; row++)
    {
        for (int col = 0; col < NUMCOLS; col++)
        {
            switch (grid[row][col].a_id)
            {
                case('R'):
                    num_rabbits++;
                    break;

                case('D'):
                    num_deer++;
                    break;

                case('W'):
                    num_wolves++;
                    break;

                case('B'):
                    num_bear++;
                    break;
            }
        }
    }
    if (num_rabbits == 0 && num_deer == 0) return 'c';
    if (num_wolves  == 0 && num_bear == 0) return 'h';
    return ' ';
}

void GUI::animal_turn(int row, int col, char type)
{
    switch(type)
    {
        case('R'):
        case('D'):
        {
            herbivore_turn(row, col, type);
            break;
        }
        case('W'):
        case('B'):
        {
            carnivore_turn(row, col, type);
            break;
        }
    }
}

void GUI::carnivore_turn(int row, int col, char type)
{
    // get the carnivore, see if it's turn is finished
    Carnivore* c = (Carnivore*)grid[row][col].get_animal();
    if (!c->get_move_made())
    {
       c->set_move_made(true);
       c->hunger();
       c->age();

       // see if the carnivore dies of old age or starvation
       if (c->get_curr_age() >= c->get_max_age()  || c->get_curr_calories() == 0)
       {
           grid[row][col].a_id = ' ';
           grid[row][col].tile_a.setColor(sf::Color::Transparent);

       }
       else // we continue the turn, as the carnivore will live
       {
          // next, will we reproduce in this turn
          determine_if_carnivore_will_reproduce(c,type);

          // get the neigboring prey squares
          vector<Ordered_Pair> neighbors = get_neighbors_that_have_only_prey(row, col);

          // if there are neighboring prey, we eat 'em!!
          if (!neighbors.empty())
          {
              /*
              cout << "And the neighbors are:" << endl;
              for (int i = 0; i < neighbors.size(); i++)
              {
                  cout << i+1 << "\t(" << neighbors[i].row << "," << neighbors[i].col << ")" << endl;
              }
              */
              // choose the first prey
              Ordered_Pair dest = get_random_move(neighbors);

              // now the carnivore can eat the prey
              carnivore_eats(dest, c, row, col);

              // move the carnivore to the new space
              grid[dest.row][dest.col].set_animal(c);
              grid[dest.row][dest.col].a_id = type;
              if (type == 'W')
              {
                   sf::Vector2f v;
                   v.x = (dest.col * TILE_SIZE);
                   v.y = (dest.row * TILE_SIZE) + 100;

                   grid[dest.row][dest.col].tile_a.setPostition(v);
                   grid[dest.row][dest.col].tile_a.setImage(c->get_Image());
              }
              else if (type == 'B')
              {
                   sf::Vector2f v;
                   v.x = (dest.col * TILE_SIZE);
                   v.y = (dest.row * TILE_SIZE) + 100;

                   grid[dest.row][dest.col].tile_a.setPostition(v);
                   grid[dest.row][dest.col].tile_a.setImage(c->get_Image());
              }

              // if the carnivore will not reproduce, we change the
              // square back to what it was
                              // change old grid square from herbivore to plant
              if(!c->get_is_pregnant())
              {
                  grid[row][col].a_id = ' ';
                  grid[row][col].set_animal(NULL);
                  grid[row][col].tile_a.setColor(sf::Color::Transparent);
              }
              else
              {
                  c->set_is_pregnant(false);

                  Carnivore* c = (Carnivore*)Factory::create_being(type);
                  grid[row][col].a_id = type;

                  sf::Vector2f v;
                  v.x = (col * TILE_SIZE);
                  v.y = (row * TILE_SIZE) + 100;

                  grid[row][col].set_animal(c);

                  grid[row][col].tile_a.setPostition(v);
                  if(type == 'W')
                  {
                      grid[row][col].tile_a.setImage(c->get_Image());
                  }
                  else if(type == 'R')
                  {
                      grid[row][col].tile_a.setImage(c->get_Image());
                  }
                }
              /*
              if(!c->get_is_pregnant())
              {
                  // set the ids
                  grid[row][col].a_id = ' ';
                  grid[row][col].set_animal(NULL);

                  // if the old square is grass
                  if (grid[row][col].p_id == 'G')
                  {
                      sf::Image img = grid[row][col].get_plant()->get_Image();
                      grid[row][col].tile_p.setImage(img);
                      grid[row][col].tile_a.setColor(sf::Color::Transparent);
                  }

                  // else it's gonna be flower
                  if (grid[row][col].p_id == 'F')
                  {
                      sf::Image img = grid[row][col].get_plant()->get_Image();
                      grid[row][col].tile_p.setImage(img);
                      grid[row][col].tile_a.setColor(sf::Color::Transparent);
                  }
               }
               else // we create a new carnivore and put it in the old square
               {
                    c->set_is_pregnant(false);

                    // create new carnivore, put it in old square
                    Carnivore* h = (Carnivore*)Factory::create_being(type);
                    grid[row][col].a_id = type;
                    sf::Vector2f v;
                    v.x = (col * TILE_SIZE);
                    v.y = (row * TILE_SIZE) + 100;
                    grid[row][col].set_animal(c);
                    grid[row][col].tile_a.setPostition(v);
                    if(type == 'W')
                    {
                        grid[row][col].tile_a.setImage(h->get_Image());
                    }
                    else if(type == 'B')
                    {
                        //cout << "creating new bear" << endl;
                        grid[row][col].tile_a.setImage(h->get_Image());
                    }
                 }
                 */
             }
             else // there are no neighbors
             {
                 // get the surrounding squares that have to predators (we already know
                 // that they have to prey), and randomly choose on to wander to
                 Ordered_Pair dest = get_square_without_fellow_predators(row, col);

                  // move the carnivore to the new space
                  grid[dest.row][dest.col].set_animal(c);
                  grid[dest.row][dest.col].a_id = type;
                  if (type == 'W')
                  {
                       sf::Vector2f v;
                       v.x = (dest.col * TILE_SIZE);
                       v.y = (dest.row * TILE_SIZE) + 100;

                       grid[dest.row][dest.col].tile_a.setPostition(v);
                       grid[dest.row][dest.col].tile_a.setImage(c->get_Image());
                  }
                  else if (type == 'B')
                  {
                       sf::Vector2f v;
                       v.x = (dest.col * TILE_SIZE);
                       v.y = (dest.row * TILE_SIZE) + 100;

                       grid[dest.row][dest.col].tile_a.setPostition(v);
                       grid[dest.row][dest.col].tile_a.setImage(c->get_Image());
                  }

                  // if the carnivore will not reproduce, we change the
                  // square back to what it was
                                  // change old grid square from herbivore to plant
                  if(!c->get_is_pregnant())
                  {
                      grid[row][col].a_id = ' ';
                      grid[row][col].set_animal(NULL);
                      grid[row][col].tile_a.setColor(sf::Color::Transparent);
                  }
                  else
                  {
                      c->set_is_pregnant(false);

                      Carnivore* c = (Carnivore*)Factory::create_being(type);
                      grid[row][col].a_id = type;

                      sf::Vector2f v;
                      v.x = (col * TILE_SIZE);
                      v.y = (row * TILE_SIZE) + 100;

                      grid[row][col].set_animal(c);

                      grid[row][col].tile_a.setPostition(v);
                      if(type == 'W')
                      {
                          grid[row][col].tile_a.setImage(c->get_Image());
                      }
                      else if(type == 'R')
                      {
                          grid[row][col].tile_a.setImage(c->get_Image());
                      }
                   }
             }
             //
             // put HUNTING CODE HERE
             //
         }
     }
 }


void GUI::herbivore_turn(int row, int col, char type)
{
    // get the rabbit, see if it's turn is finished
    Herbivore* h = (Herbivore*)grid[row][col].get_animal();
    if (!h->get_move_made())
    {
       h->set_move_made(true);

       h->hunger();
       h->age();

       if (h->get_curr_age() >= h->get_max_age() || h->get_curr_calories() == 0)
       {
           h->die();
           //delete[] &h;
           //grid[row][col].set_animal(NULL);
           //cout << "Dead Herbivore" << endl;
           grid[row][col].a_id = ' ';
           grid[row][col].tile_a.setColor(sf::Color::Transparent);

       }
       else
       {
           vector<Ordered_Pair> neighbors = get_neighbors_that_have_only_plants(row, col);
            if (!neighbors.empty()) // else the turn ends
            {
                Ordered_Pair dest = get_neighbor_with_highest_caloric_yield(neighbors);

                // next, will we reproduce in this turn
                determine_if_herbivore_will_reproduce(h,type);
                //if (will_reproduce) cout << "Rabbit may be born" << endl;

                // move to grid space
                grid[dest.row][dest.col].set_animal(h);
                grid[dest.row][dest.col].a_id = type;
                if (type == 'R')
                {
                   sf::Vector2f v;
                   v.x = (dest.col * TILE_SIZE);
                   v.y = (dest.row * TILE_SIZE) + 100;

                   grid[dest.row][dest.col].tile_a.setPostition(v);
                   grid[dest.row][dest.col].tile_a.setImage(h->get_Image());
                }
                else if (type == 'D')
                {
                   sf::Vector2f v;
                   v.x = (dest.col * TILE_SIZE);
                   v.y = (dest.row * TILE_SIZE) + 100;

                   grid[dest.row][dest.col].tile_a.setPostition(v);
                   grid[dest.row][dest.col].tile_a.setImage(h->get_Image());
                }

                // change old grid square from herbivore to plant
                if(!h->get_is_pregnant()){

                    grid[row][col].a_id = ' ';
                    grid[row][col].set_animal(NULL);
                    //if (grid[row][col].p_id == 'G')
                    //{
                        //sf::Image img = grid[row][col].get_plant()->get_Image();
                        //grid[row][col].tile_p.setImage(img);
                        grid[row][col].tile_a.setColor(sf::Color::Transparent);

                }
                else
                {
                    h->set_is_pregnant(false);

                    Herbivore* h = (Herbivore*)Factory::create_being(type);
                    grid[row][col].a_id = type;

                    sf::Vector2f v;
                    v.x = (col * TILE_SIZE);
                    v.y = (row * TILE_SIZE) + 100;

                    grid[row][col].set_animal(h);

                    grid[row][col].tile_a.setPostition(v);
                    if(type == 'D'){
                        grid[row][col].tile_a.setImage(h->get_Image());
                    }
                    else if(type == 'R'){
                        grid[row][col].tile_a.setImage(h->get_Image());
                    }

                }

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
                    if(h->get_curr_calories() < h->get_max_calories()){
                        herbivore_eats(dest, h);
                    }
                    /*
                    if (h->get_is_pregnant())
                    {
                        h->set_is_pregnant(false);
                    }
                    */
               }
           }
       }
    }
}

Ordered_Pair GUI::get_square_without_fellow_predators(int row, int col)
{
    vector <Ordered_Pair> neighbors;
    // look up to the left
    if (row - 1 >= 0 && col - 1 >= 0)
    {
        if (grid[row-1][col-1].a_id == ' ')
        {
            Ordered_Pair n;
            n.row = row-1;
            n.col = col-1;
            neighbors.push_back(n);
        }
    }

    // look up
    if (row - 1 >= 0)
    {
        if (grid[row-1][col].a_id == ' ')
        {
            Ordered_Pair n;
            n.row = row-1;
            n.col = col;
            neighbors.push_back(n);
        }
    }

    // look up to the right
    if (row-1 >= 0 && col+1 < NUMCOLS)
    {
        if (grid[row-1][col+1].a_id == ' ')
        {
            Ordered_Pair n;
            n.row = row-1;
            n.col = col+1;
            neighbors.push_back(n);
        }
    }

    // look left
    if (col - 1 >= 0)
    {
        if (grid[row][col-1].a_id == ' ')
        {
            Ordered_Pair n;
            n.row = row;
            n.col = col-1;
            neighbors.push_back(n);
        }
    }

    // look right
    if (col+1 < NUMCOLS)
    {
        if (grid[row][col+1].a_id == ' ')
        {
            Ordered_Pair n;
            n.row = row;
            n.col = col+1;
            neighbors.push_back(n);
        }
    }

    // look down and to the left
    if (row+1 < NUMROWS && col-1 >= 0)
    {
        if (grid[row+1][col-1].a_id == ' ')
        {
            Ordered_Pair n;
            n.row = row+1;
            n.col = col-1;
            neighbors.push_back(n);
        }
    }

    // look down
    if (row+1 < NUMROWS)
    {
        if (grid[row+1][col].a_id == ' ')
        {
            Ordered_Pair n;
            n.row = row+1;
            n.col = col;
            neighbors.push_back(n);
        }
    }

    // look down and to the right
    if (row+1 < NUMROWS && row+1 < NUMCOLS)
    {
        if (grid[row+1][col+1].a_id == ' ')
        {
            Ordered_Pair n;
            n.row = row+1;
            n.col = col+1;
            neighbors.push_back(n);
        }
    }

    Ordered_Pair dest;
    if (neighbors.empty())
    {
        dest.row = row;
        dest.col = col;
    }
    else
    {
        int ran_num = rand()%neighbors.size();
        dest.row = neighbors[ran_num].row;
        dest.col = neighbors[ran_num].col;
    }
    cout << "Random destination is (" << dest.row << "," << dest.col << ")" << endl;
    return dest;
}

void GUI::carnivore_eats(Ordered_Pair dest, Carnivore* h, int row, int col)
{
    if (grid[dest.row][dest.col].a_id == 'R')
    {
        Rabbit* r = (Rabbit*)grid[dest.row][dest.col].get_animal();
        if (grid[row][col].a_id == 'W')
        {
            Wolf *w = (Wolf*)grid[row][col].get_animal();
            if (r->get_curr_calories() < w->get_calories_per_rabbit())
            {
                w->eat(r->get_curr_calories());
            }
            else
            {
                w->eat(w->get_calories_per_rabbit());
            }
       //     delete[]&r;
        }
        else // it's a bear
        {
            Bear *b = (Bear*)grid[row][col].get_animal();
            if (r->get_curr_calories() < b->get_calories_per_rabbit())
            {
                b->eat(r->get_curr_calories());
            }
            else
            {
                b->eat(b->get_calories_per_rabbit());
            }
        //    delete[]&r;
        }
    }
    else // it's a deer
    {
        Deer* d = (Deer*)grid[dest.row][dest.col].get_animal();
        if (grid[row][col].a_id == 'W')
        {
            Wolf *w = (Wolf*)grid[row][col].get_animal();
            if (d->get_curr_calories() < w->get_calories_per_deer())
            {
                w->eat(d->get_curr_calories());
            }
            else
            {
                w->eat(w->get_calories_per_deer());
            }
        }
        else // it's a bear
        {
            Bear *b = (Bear*)grid[row][col].get_animal();
            if (d->get_curr_calories() < b->get_calories_per_rabbit())
            {
                b->eat(d->get_curr_calories());
            }
            else
            {
                b->eat(b->get_calories_per_deer());
            }
        }
    }
}

void GUI::herbivore_eats(Ordered_Pair dest, Herbivore* h)
{
    // get the number of calories that we can eat
    int curr_eat = 5;

     if (grid[dest.row][dest.col].p_id != ' ')
     {
        //if the grass only has <= calories per grass, then we just kill the grass
        Plant* p = (Plant*)grid[dest.row][dest.col].get_plant();
       // eat less than 5
        if (p->get_curr_calories() <= curr_eat)
        {
            h->eat(p->get_curr_calories());
            delete[] &p;
            grid[dest.row][dest.col].set_plant(NULL);
            grid[dest.row][dest.col].p_id = ' ';
            Plant* new_p = (Plant*) new Empty();
            grid[dest.row][dest.col].set_plant(new_p);
            grid[dest.row][dest.col].tile_p.setImage(new_p->get_Image());

        }
        else {
            int chunk = p->get_curr_calories() / p->get_plant_rate();
            chunk += 5;
            if(chunk > (p->get_max_calories() - p->get_curr_calories()))
            {
                chunk = 5;
            }

            p->remove_calories(chunk);
            h->eat(chunk);
        }
    }
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


void GUI::determine_if_carnivore_will_reproduce(Carnivore* c,char type)
{

    if (c->get_curr_calories() >= c->get_min_calories_to_reproduce() &&
    c->get_curr_age() >= c->get_min_age_to_reproduce())
    {

        int num =  rand()%100+1;
        if (num < c->get_reproductive_rate())
        {
            c->set_is_pregnant(true);
        }
    }
}

void GUI::determine_if_herbivore_will_reproduce(Herbivore* h,char type)
{

    if (h->get_curr_calories() >= h->get_min_calories_to_reproduce() &&
        h->get_curr_age() >= h->get_min_age_to_reproduce())
    {
        int num =  rand()%100+1;
        if (num < h->get_reproductive_rate())
        {
            h->set_is_pregnant(true);
        }
    }


}


Ordered_Pair GUI::get_neighbor_with_highest_caloric_yield(vector<Ordered_Pair>neighbors)
{
    /*
    Ordered_Pair best_neighbor;
    best_neighbor.row = -999;
    best_neighbor.col = 0;
    int calories = 0;
    //cout << "yield starts" << endl;
    for (unsigned int i = 0; i < neighbors.size(); i++){

        if(grid[neighbors[i].row][neighbors[i].col].a_id != ' '){
            cout << "Animal detected in the pool of moves" << endl;
            cout << "Exiting program." << endl;
            exit(EXIT_FAILURE);
        }

    }
    // go through each square and get the plant with the highest yield
    for (unsigned int i = 0; i < neighbors.size(); i++)
    {
        if(grid[neighbors[i].row][neighbors[i].col].p_id != ' ')
        {
            Plant* p = (Plant*)grid[neighbors[i].row][neighbors[i].col].get_plant();
            if (p->get_curr_calories() > calories)
            {
                best_neighbor.row = neighbors[i].row;
                best_neighbor.col = neighbors[i].col;
                calories = p->get_curr_calories();
            }
            else if(p->get_curr_calories() < calories){
                    neighbors.erase(neighbors.begin() + i);
                    --i;
            }
        }

    }
    */

    //choosing movement randomly
    int r = rand() % neighbors.size();
    Ordered_Pair best_neighbor;
    best_neighbor.row = neighbors[r].row;
    best_neighbor.col = neighbors[r].col;


    return best_neighbor;
}

vector<Ordered_Pair> GUI::get_neighbors_that_have_only_prey(int row,int col)
{
    vector <Ordered_Pair> neighbors;
    // look up to the left
    if (row - 1 >= 0 && col - 1 >= 0)
    {
        if (grid[row-1][col-1].a_id != ' ')
        {
            if (grid[row-1][col-1].a_id == 'R' || grid[row-1][col-1].a_id == 'D')
            {
                Ordered_Pair n;
                n.row = row-1;
                n.col = col-1;
                neighbors.push_back(n);
            }
        }
    }

    // look up
    if (row - 1 >= 0)
    {
        if (grid[row-1][col].a_id != ' ')
        {
            if (grid[row-1][col].a_id == 'R' || grid[row-1][col].a_id == 'D')
            {
                Ordered_Pair n;
                n.row = row-1;
                n.col = col;
                neighbors.push_back(n);
            }
        }
    }

    // look up to the right
    if (row-1 >= 0 && col+1 < NUMCOLS)
    {
        if (grid[row-1][col+1].a_id != ' ')
        {
            if (grid[row-1][col+1].a_id == 'R' || grid[row-1][col+1].a_id == 'D')
            {
                Ordered_Pair n;
                n.row = row-1;
                n.col = col+1;
                neighbors.push_back(n);
            }
        }
    }

    // look left
    if (col - 1 >= 0)
    {
        if (grid[row][col-1].a_id != ' ')
        {
            if (grid[row][col-1].a_id == 'R' || grid[row][col-1].a_id == 'D')
            {
                Ordered_Pair n;
                n.row = row;
                n.col = col-1;
                neighbors.push_back(n);
            }
        }
    }

    // look right
    if (col+1 < NUMCOLS)
    {
        if (grid[row][col+1].a_id != ' ')
        {
            if (grid[row][col+1].a_id == 'R' || grid[row][col+1].a_id == 'D')
            {
                Ordered_Pair n;
                n.row = row;
                n.col = col+1;
                neighbors.push_back(n);
            }
        }
    }

    // look down and to the left
    if (row+1 < NUMROWS && col-1 >= 0)
    {
        if (grid[row+1][col-1].a_id != ' ')
        {
            if (grid[row+1][col-1].a_id == 'R' || grid[row+1][col-1].a_id == 'D')
            {
                Ordered_Pair n;
                n.row = row+1;
                n.col = col-1;
                neighbors.push_back(n);
            }
        }
    }

    // look down
    if (row+1 < NUMROWS)
    {
        if (grid[row+1][col].a_id != ' ')
        {
            if (grid[row+1][col].a_id == 'R' || grid[row+1][col].a_id == 'D')
            {
                Ordered_Pair n;
                n.row = row+1;
                n.col = col;
                neighbors.push_back(n);
            }
        }
    }

    // look down and to the right
    if (row+1 < NUMROWS && row+1 < NUMCOLS)
    {
        if (grid[row+1][col+1].a_id != ' ')
        {
            if (grid[row+1][col+1].a_id == 'R' || grid[row+1][col+1].a_id == 'D')
            {
                Ordered_Pair n;
                n.row = row+1;
                n.col = col+1;
                neighbors.push_back(n);
            }
        }
    }

    return neighbors;
}

vector<Ordered_Pair> GUI::get_neighbors_that_have_only_plants(int row, int col)
{
    vector<Ordered_Pair> all_moves;
    for(int i = 0;i < 3;++i)
    {
        for(int j = 0;j < 3;++j)
        {
            Ordered_Pair p;
            p.col = i-1+col;
            p.row = j-1+row;
            all_moves.push_back(p);
        }

        //removing unwanted moves
        for(unsigned int i = 0;i < all_moves.size();++i)
        {
            int c = all_moves[i].col;
            int r = all_moves[i].row;

            //removing spot where object resides
            if(c == col && r == row)
            {
                //cout << "popping out center itself" << endl;
                all_moves.erase(all_moves.begin() + i);
                --i;
            }
        }

        for(unsigned int i = 0;i < all_moves.size();++i)
        {
            int c = all_moves[i].col;
            int r = all_moves[i].row;

            //removing spot where object resides
            if(c < 0 || r < 0 || c > NUMCOLS-1 || r > NUMROWS-1)
            {
               all_moves.erase(all_moves.begin() + i);
                --i;
            }
        }

        for(unsigned int i = 0;i < all_moves.size();++i)
        {
            int c = all_moves[i].col;
            int r = all_moves[i].row;

            //removing spot where object resides
            if( grid[r][c].a_id != ' ')
            {
                all_moves.erase(all_moves.begin() + i);
                --i;
            }
        }
    }
    return all_moves;
}





void GUI::drawGrid(){
    for(int i = 0;i < 40; ++i){
        for(int j = 0;j < 30; ++j)
        {
            app->draw(grid[j][i].tile_p.sprite);
            app->draw(grid[j][i].tile_a.sprite);
        }
    }
}



void GUI::populate_grid()
{
    // populates the grass
    create_grass_and_flowers();
    create_animals();

}

void GUI::create_grass_and_flowers()
{
    // create the array
    int size = NUMCOLS*NUMROWS;
    vector<char> pool(size);
    int i = 0;

    // put in the grass
    int curr_size = NUMGRASS;
    for (i = 0;i < curr_size;++i){
        pool[i] = 'G';
    }

    // put in the flowers
    curr_size += NUMFLOWERS;
    //populating the rest flower
    for (;i < curr_size;++i){
        pool[i] = 'F';
    }

    // put in spaces for the rest
    for (;i < size;++i){
        pool[i] = ' ';
    }

    // shuffle the board
    std::random_shuffle ( pool.begin(), pool.end() );

    int counter = 0;
    for(int r = 0; r < NUMROWS;++r)
    {
        for(int c = 0; c < NUMCOLS;++c)
        {
            char type = pool[counter++];
            if(type != ' ')
            {
                Plant* g = (Plant*)Factory::create_being(type);
                sf::Vector2f v;
                v.x = (c * TILE_SIZE);
                v.y = (r * TILE_SIZE) + 100;

                grid[r][c].set_plant(g);
                grid[r][c].p_id = type;
                grid[r][c].a_id = ' ';

                grid[r][c].tile_p.setPostition(v);
                grid[r][c].tile_p.setImage(g->get_Image());
            }
            else
            {
                Plant* g = (Plant*)Factory::create_being('P');
                sf::Vector2f v;
                v.x = (c * TILE_SIZE);
                v.y = (r * TILE_SIZE) + 100;

                grid[r][c].set_plant(g);
                grid[r][c].p_id = ' ';
                grid[r][c].a_id = ' ';

                grid[r][c].tile_p.setPostition(v);
                grid[r][c].tile_p.setImage(g->get_Image());
            }
        }
    }
}

void GUI::create_animals()
{
    // create the array that will hold everything
    int size = NUMCOLS*NUMROWS;
    vector<char> pool(size);
    int i = 0;

    // put in the rabbits
    int curr_size = NUMRABBITS;
    //populating grass
    for (i = 0;i < curr_size;++i){
        pool[i] = 'R';
    }

    // put in the deer
    curr_size += NUMDEER;
    for (;i < curr_size;++i){
        pool[i] = 'D';
    }

    // put in the wolves
    curr_size += NUMWOLVES;
    for (;i < curr_size;++i){
        pool[i] = 'W';
    }

    // put in the bears
    curr_size += NUMBEAR;
    for (;i < curr_size; ++i){
        pool[i] = 'B';
    }

    // put spaces in for the rest
    for (;i < size;++i){
        pool[i] = ' ';
    }

    // shuffle the board
    std::random_shuffle (pool.begin(), pool.end());

    /*
    // print the board to see that it's correct
    for (int i = 0; i < size; i++) {
        cout << i << " " << pool[i] << "\t";
        if (i%3 == 0) cout << endl;
    }
    */


    int counter = 0;
    for(int r = 0; r < NUMROWS;++r)
    {
        for(int c = 0; c < NUMCOLS;++c)
        {
            char type = pool[counter++];

            // put in the herbivores
            if(type == 'R' || type == 'D')
            {
                Herbivore* h = (Herbivore*)Factory::create_being(type);
                sf::Vector2f v;
                v.x = (c * TILE_SIZE);
                v.y = (r * TILE_SIZE) + 100;

                grid[r][c].set_animal(h);
                grid[r][c].a_id = type;

                grid[r][c].tile_a.setPostition(v);
                grid[r][c].tile_a.setImage(h->get_Image());
            }

            // put in the carnivores
            if (type == 'W' || type == 'B')
            {
                Carnivore* ca = (Carnivore*)Factory::create_being(type);
                sf::Vector2f v;
                v.x = (c * TILE_SIZE);
                v.y = (r * TILE_SIZE) + 100;

                grid[r][c].set_animal(ca);
                grid[r][c].a_id = type;

                grid[r][c].tile_a.setPostition(v);
                grid[r][c].tile_a.setImage(ca->get_Image());
            }
        }
    }
}

void GUI::print_ASCII(char type)
{
    if(type == 'p')
    {
        for (int i = 0; i < NUMROWS;++i)
        {
            for(int j = 0;j < NUMCOLS;++j)
            {
                cout << "[" << grid[i][j].p_id << "]";
            }
            cout << endl;
        }
    }
    else
    {
        for (int i = 0; i < NUMROWS;++i)
        {
            for(int j = 0;j < NUMCOLS;++j)
            {
                cout << "[" << grid[i][j].a_id << "]";
            }
            cout << endl;
        }
    }
    cout << endl << endl;
}

Ordered_Pair GUI::get_random_move(vector<Ordered_Pair> neighbors)
{
    Ordered_Pair dest;
    int r = rand() % neighbors.size();
    dest.row = neighbors[r].row;
    dest.col = neighbors[r].col;
    return dest;
}
