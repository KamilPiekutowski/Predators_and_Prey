#ifndef CARNIVORE_H
#define CARNIVORE_H
#include <Living_Being.h>

class Carnivore : public Predator
{
private:
    // miscellaneous variables
    int max_age;
    int curr_age;


    // food-related variables
    int max_calories;
    int curr_calories;
    int min_calories_to_eat;
    int metabolic_rate;
    int calories_per_rabbit;
    int calories_per_deer;

    // reproduction variables
    int reproductive_rate;
    int min_age_to_reproduce;
    int min_calories_to_reproduce;

    // evasion variables
    int min_calories_to_hunt;

    //bools
    bool move_made;
    bool is_pregnant;

public:
    Carnivore();
    virtual ~Carnivore();

    //inherited methods
    void hunt();
    void die();
    void hunger();
    void move();
    void reproduce();
    void eat(int);
    void take_turn();
    void age();

    //getters/setters
    bool get_is_pregnant();
    void set_is_pregnant(bool);
    bool get_move_made();
    void set_move_made(bool);
    int get_max_age();
    void set_max_age(int);
    int get_curr_age();
    void set_curr_age(int);
    int get_max_calories();
    void set_max_calories(int);
    int get_curr_calories();
    void set_curr_calories(int);
    int get_metabolic_rate();
    void set_min_calories_to_eat(int);
    int get_min_calories_to_eat();
    void set_metabolic_rate(int);
    void set_calories_per_rabbit(int);
    int get_calories_per_rabbit();
    void set_calories_per_deer(int);
    int get_calories_per_deer();
    int get_reproductive_rate();
    void set_reproductive_rate(int);
    int get_min_age_to_reproduce();
    void set_min_age_to_reproduce(int);
    int get_min_calories_to_reproduce();
    void set_min_calories_to_reproduce(int);
    void set_min_calories_to_hunt(int);
    int get_min_calories_to_hunt();
};

#endif // CARNIVORE_H
