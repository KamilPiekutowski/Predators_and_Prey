#ifndef HERBIVORE_H
#define HERBIVORE_H
#include <Living_Being.h>


class Herbivore : public Prey
{
private:
    // miscellaneous variables
    int max_age;
    int curr_age;


    // food-related variables
    int max_calories;
    int curr_calories;
    int metabolic_rate;
    int calories_per_grass;
    int calories_per_20_grass;
    int calories_per_flower;
    int calories_per_30_flowers;

    // reproduction variables
    int reproductive_rate;
    int min_age_to_reproduce;
    int min_calories_to_reproduce;

    // evasion variables
    int min_calories_to_evade;

    //bools
    bool move_made;
    bool is_pregnant;

 public:
    Herbivore();
    ~Herbivore();

    // public variables


    // inherited methods
    void evade();
    void die();
    void hunger();
    void move();
    void reproduce();
    void eat(int);
    void take_turn();
    void age();

    // getters/setters

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
    void set_metabolic_rate(int);
    int get_calories_per_grass();
    void set_calories_per_grass(int);
    int get_calories_per_20_grass();
    void set_calories_per_20_grass(int);
    int get_calories_per_flower();
    void set_calories_per_flower(int);
    int get_calories_per_30_flowers();
    void set_calories_per_30_flowers(int);
    int get_reproductive_rate();
    void set_reproductive_rate(int);
    int get_min_age_to_reproduce();
    void set_min_age_to_reproduce(int);
    int get_min_calories_to_reproduce();
    void set_min_calories_to_reproduce(int);
    int get_min_calories_to_evade();
    void set_min_calories_to_evade(int);
};
#endif // HERBIVORE_H
