#ifndef LIVING_BEING_H
#define LIVING_BEING_H

#include <stdlib.h>
#include <iostream>
using namespace std;

class Living_Being
{
    virtual void eat(int) = 0;
    virtual void die()    = 0;
};

class Mammal : public Living_Being
{
    virtual void die()           = 0;
    virtual void hunger()        = 0;
    virtual void move()          = 0;
    virtual void reproduce()     = 0;
    virtual void eat(int)        = 0;
};

class Prey : public Mammal
{
    virtual void evade() = 0;
};

class Predator : public Mammal
{
    virtual void hunt() = 0;
};

///////////// Plants //////////////////
class Grass : public Living_Being
{
private:
    int  max_calories;
    int  curr_calories;

public:
    // constructor
    Grass()
    {
        set_curr_calories(30);
        set_max_calories(100);
    }

    // destructor
    ~Grass(){}

    // inherited methods
    void eat(int num_calories)
    {
        set_curr_calories(get_curr_calories()+num_calories);
    }

    void die()
    {
        cout << "And the blade of grass is dead..." << endl;
    }

    // getters/setters
    int get_max_calories()
    { return max_calories; }

    void set_max_calories(int m)
    { max_calories = m; }

    int get_curr_calories()
    { return curr_calories; }

    void set_curr_calories(int c)
    { curr_calories = c; }
};

class Flower : public Living_Being
{
private:
    int  max_calories;
    int  curr_calories;
public:

    // constructor
    Flower()
    {
        set_curr_calories(30);
        set_max_calories(150);
    }

    // destructor
    ~Flower(){}

    // inherited methods
    void eat(int num_calories)
    {
        set_curr_calories(get_curr_calories()+num_calories);
    }

    void die()
    {
        cout << "And the beautiful flower is dead..." << endl;
    }

    // getters/setters
    int get_max_calories()
    { return max_calories; }

    void set_max_calories(int m)
    { Flower::max_calories = m; }

    int get_curr_calories()
    { return curr_calories; }

    void set_curr_calories(int c)
    { Flower::curr_calories = c; }
};
//////////// End Plants ///////////////

//////////// Prey ////////////////////

class Rabbit : public Prey
{
private:
    // miscellaneous variables
    int max_age;
    int curr_age;
    int index;

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

public:

    // constructor
    Rabbit()
    {
        set_index(0);
        set_max_age(25);
        set_curr_age(0);
        set_max_calories(45);
        set_curr_calories(10);
        set_metabolic_rate(3);
        set_calories_per_grass(5);
        set_calories_per_20_grass(1);
        set_calories_per_flower(6);
        set_calories_per_30_flowers(2);
        set_reproductive_rate(50);
        set_min_age_to_reproduce(10);
        set_min_calories_to_reproduce(40);
        set_min_calories_to_evade(30);
    };

    // destructor
    ~Rabbit(){}

    // inherited methods
    void eat(int num_calories)
    {
        set_curr_calories(get_curr_calories()+num_calories);
    }

    void die()
    {

    }

    void age()
    {
        set_curr_age(get_curr_age()+1);
    }

    void hunger()
    {
        set_curr_calories(get_curr_calories() - get_metabolic_rate());
    }

    void move()
    {
        cout << "The rabbit moves." << endl;
    }

    void evade()
    {
        cout << "The rabbit runs away!" << endl;
    }

    void reproduce()
    {
        cout << "A bunny is born!" << endl;
    }

    // getters/setters
    void set_index(int x)
    { index = x;}

    int get_index()
    { return index; }

    int get_max_age()
    { return max_age; }

    void set_max_age(int ma)
    { max_age = ma; }

    int get_curr_age()
    { return curr_age; }

    void set_curr_age(int ca)
    { curr_age = ca; }

    int get_max_calories()
    { return max_calories; }

    void set_max_calories(int mc)
    { max_calories = mc; }

    int get_curr_calories()
    { return curr_calories; }

    void set_curr_calories(int cc)
    { curr_calories = cc; }

    int get_metabolic_rate()
    { return metabolic_rate; }

    void set_metabolic_rate(int mr)
    { metabolic_rate = mr; }

    int get_calories_per_grass()
    { return calories_per_grass; }

    void set_calories_per_grass(int cpg)
    { calories_per_grass = cpg; }

    int get_calories_per_20_grass()
    { return calories_per_20_grass; }

    void set_calories_per_20_grass(int cp20g)
    { calories_per_20_grass = cp20g; }

    int get_calories_per_flower()
    { return calories_per_flower; }

    void set_calories_per_flower(int cpf)
    { calories_per_flower = cpf; }

    int get_calories_per_30_flowers()
    { return calories_per_30_flowers; }

    void set_calories_per_30_flowers(int cp30f)
    { calories_per_30_flowers = cp30f; }

    int get_reproductive_rate()
    { return reproductive_rate; }

    void set_reproductive_rate(int rr)
    { reproductive_rate = rr; }

    int get_min_age_to_reproduce()
    { return min_age_to_reproduce; }

    void set_min_age_to_reproduce(int mar)
    { min_age_to_reproduce = mar; }

    int get_min_calories_to_reproduce()
    { return min_calories_to_reproduce; }

    void set_min_calories_to_reproduce(int mcr)
    { min_calories_to_reproduce = mcr; }

    int get_min_calories_to_evade()
    { return min_calories_to_evade; }

    void set_min_calories_to_evade(int mce)
    { min_calories_to_evade = mce; }


};

class Deer : public Prey
{
private:
    // miscellaneous variables
    int max_age;
    int curr_age;
    int index;


    // food-related variables
    int max_calories;
    int curr_calories;
    int metabolic_rate;
    int calories_per_grass;
    int calories_per_30_grass;
    int calories_per_flower;
    int calories_per_40_flowers;

    // reproduction variables
    int reproductive_rate;
    int min_age_to_reproduce;
    int min_calories_to_reproduce;

    // evasion variables
    int min_calories_to_evade;

public:

    // constructor
    Deer()
    {
        set_index(0);
        set_max_age(30);
        set_curr_age(0);
        set_max_calories(55);
        set_curr_calories(15);
        set_metabolic_rate(4);
        set_calories_per_grass(7);
        set_calories_per_30_grass(2);
        set_calories_per_flower(7);
        set_calories_per_40_flowers(3);
        set_reproductive_rate(40);
        set_min_age_to_reproduce(12);
        set_min_calories_to_reproduce(40);
        set_min_calories_to_evade(35);
    };

    // destructor
    ~Deer(){}

    // inherited methods
    void eat(int num_calories)
    {
        set_curr_calories(get_curr_calories()+num_calories);
    }

    void die()
    {
        cout << "Bambi is dead." << endl;
    }

    void die_of_hunger(){}

    void hunger()
    {
        set_curr_calories(get_curr_calories() - get_metabolic_rate());
    }

    void move()
    {
        cout << "The deer wanders off." << endl;
    }

    void age()
    {
        set_curr_age(get_curr_age()+1);
    }

    void evade()
    {
        cout << "The dear bounds away." << endl;
    }

    void reproduce()
    {
        cout << "Bambi is born." << endl;
    }

    // getters/setters
    void set_index(int x)
    { index = x;}

    int get_index()
    { return index; }

    int get_max_age()
    { return max_age; }

    void set_max_age(int ma)
    { max_age = ma; }

    int get_curr_age()
    { return curr_age; }

    void set_curr_age(int ca)
    { curr_age = ca; }

    int get_max_calories()
    { return max_calories; }

    void set_max_calories(int mc)
    { max_calories = mc; }

    int get_curr_calories()
    { return curr_calories; }

    void set_curr_calories(int cc)
    { curr_calories = cc; }

    int get_metabolic_rate()
    { return metabolic_rate; }

    void set_metabolic_rate(int mr)
    { metabolic_rate = mr; }

    int get_calories_per_grass()
    { return calories_per_grass; }

    void set_calories_per_grass(int cpg)
    { calories_per_grass = cpg; }

    int get_calories_per_30_grass()
    { return calories_per_30_grass; }

    void set_calories_per_30_grass(int cp20g)
    { calories_per_30_grass = cp20g; }

    int get_calories_per_flower()
    { return calories_per_flower; }

    void set_calories_per_flower(int cpf)
    { calories_per_flower = cpf; }

    int get_calories_per_40_flowers()
    { return calories_per_40_flowers; }

    void set_calories_per_40_flowers(int cp40f)
    { calories_per_40_flowers = cp40f; }

    int get_reproductive_rate()
    { return reproductive_rate; }

    void set_reproductive_rate(int rr)
    { reproductive_rate = rr; }

    int get_min_age_to_reproduce()
    { return min_age_to_reproduce; }

    void set_min_age_to_reproduce(int mar)
    { min_age_to_reproduce = mar; }

    int get_min_calories_to_reproduce()
    { return min_calories_to_reproduce; }

    void set_min_calories_to_reproduce(int mcr)
    { min_calories_to_reproduce = mcr; }

    int get_min_calories_to_evade()
    { return min_calories_to_evade; }

    void set_min_calories_to_evade(int mce)
    { min_calories_to_evade = mce; }
};
/////////// End Prey /////////////////

/////////// Predators ////////////////
class Wolf : public Predator
{
private:
    // miscellaneous variables
    int max_age;
    int curr_age;
    int index;

    // food-related variables
    int max_calories;
    int curr_calories;
    int metabolic_rate;
    int calories_per_rabbit;
    int calories_per_deer;
    int min_calories_to_eat;

    // reproduction variables
    int reproductive_rate;
    int min_age_to_reproduce;
    int min_calories_to_reproduce;

    // hunting variables
    int min_calories_to_hunt;

public:
    // constructor
    Wolf()
    {
        set_index(0);
        set_min_calories_to_eat(190);
        set_max_age(50);
        set_curr_age(0);
        set_max_calories(200);
        set_curr_calories(150);
        set_metabolic_rate(2);
        set_calories_per_rabbit(10);
        set_calories_per_deer(13);
        set_reproductive_rate(40);
        set_min_age_to_reproduce(10);
        set_min_calories_to_reproduce(120);
        set_min_calories_to_hunt(40);
    }

    // destructor
    ~Wolf(){}

    // inherited methods
    void eat(int num_calories)
    {
        set_curr_calories(get_curr_calories()+num_calories);
    }

    void die()
    {
        cout << "The wolf dies." << endl;
    }


    void hunger()
    {
        set_curr_calories(get_curr_calories() - get_metabolic_rate());
    }

    void move()
    {
        cout << "The wolf prowls around." << endl;
    }

    void age()
    {
        set_curr_age(get_curr_age()+1);
    }

    void hunt()
    {
        cout << "The wolf stalks its prey." << endl;
    }

    void reproduce()
    {
        cout << "Wolf cubs are super adorable!" << endl;
    }

    // getters/setters
    void set_index(int x)
    { index = x;}

    int get_index()
    { return index; }

    void set_min_calories_to_eat(int m)
    { min_calories_to_eat = m;}

    int get_min_calories_to_eat()
    { return min_calories_to_eat; }

    int get_max_age()
    { return max_age; }

    void set_max_age(int ma)
    { max_age = ma; }

    int get_curr_age()
    { return curr_age; }

    void set_curr_age(int ca)
    { curr_age = ca; }

    int get_max_calories()
    { return max_calories; }

    void set_max_calories(int mc)
    { max_calories = mc; }

    int get_curr_calories()
    { return curr_calories; }

    void set_curr_calories(int cc)
    { curr_calories = cc; }

    int get_metabolic_rate()
    { return metabolic_rate; }

    void set_metabolic_rate(int mr)
    { metabolic_rate = mr; }

    int get_calories_per_rabbit()
    { return calories_per_rabbit; }

    void set_calories_per_rabbit(int cpr)
    { calories_per_rabbit = cpr; }

    int get_calories_per_deer()
    { return calories_per_deer; }

    void set_calories_per_deer(int cpd)
    { calories_per_deer = cpd; }

    int get_reproductive_rate()
    { return reproductive_rate; }

    void set_reproductive_rate(int rr)
    { reproductive_rate = rr; }

    int get_min_age_to_reproduce()
    { return min_age_to_reproduce; }

    void set_min_age_to_reproduce(int mar)
    { min_age_to_reproduce = mar; }

    int get_min_calories_to_reproduce()
    { return min_calories_to_reproduce; }

    void set_min_calories_to_reproduce(int mcr)
    { min_calories_to_reproduce = mcr; }

    int get_min_calories_to_hunt()
    { return min_calories_to_hunt; }

    void set_min_calories_to_hunt(int mch)
    { min_calories_to_hunt = mch; }
};

class Bear : public Predator
{
private:
// miscellaneous variables
    int max_age;
    int curr_age;
    int index;

    // food-related variables
    int max_calories;
    int curr_calories;
    int metabolic_rate;
    int calories_per_rabbit;
    int calories_per_deer;
    int min_calories_to_eat;

    // reproduction variables
    int reproductive_rate;
    int min_age_to_reproduce;
    int min_calories_to_reproduce;

    // hunting variables
    int min_calories_to_hunt;

public:
    // constructor
    Bear()
    {
        set_index(0);
        set_min_calories_to_eat(150);
        set_max_age(60);
        set_curr_age(0);
        set_max_calories(250);
        set_curr_calories(100);
        set_metabolic_rate(3);
        set_calories_per_rabbit(13);
        set_calories_per_deer(15);
        set_reproductive_rate(35);
        set_min_age_to_reproduce(20);
        set_min_calories_to_reproduce(200);
        set_min_calories_to_hunt(30);
    }

    // destructor
    ~Bear(){}

    // inherited methods
    void eat(int num_calories)
    {
        set_curr_calories(get_curr_calories()+num_calories);
    }

    void die()
    {
        cout << "The bear dies." << endl;
    }

    void die_of_hunger(){}

    void hunger()
    {
        set_curr_calories(get_curr_calories() - get_metabolic_rate());
    }

    void move()
    {
        cout << "The bear pads around" << endl;
    }

    void hunt()
    {
        cout << "You don't have to outrun the bear, just outrun me." << endl;
    }

    void age()
    {
        set_curr_age(get_curr_age()+1);
    }

    void reproduce()
    {
        cout << "Bear cubs!" << endl;
    }

    // getters/setters
    void set_index(int x)
    { index = x;}

    int get_index()
    { return index; }

    void set_min_calories_to_eat(int m)
    { min_calories_to_eat = m; }

    int get_min_calories_to_eat()
    { return min_calories_to_eat; }

    int get_max_age()
    { return max_age; }

    void set_max_age(int ma)
    { max_age = ma; }

    int get_curr_age()
    { return curr_age; }

    void set_curr_age(int ca)
    { curr_age = ca; }

    int get_max_calories()
    { return max_calories; }

    void set_max_calories(int mc)
    { max_calories = mc; }

    int get_curr_calories()
    { return curr_calories; }

    void set_curr_calories(int cc)
    { curr_calories = cc; }

    int get_metabolic_rate()
    { return metabolic_rate; }

    void set_metabolic_rate(int mr)
    { metabolic_rate = mr; }

    int get_calories_per_rabbit()
    { return calories_per_rabbit; }

    void set_calories_per_rabbit(int cpr)
    { calories_per_rabbit = cpr; }

    int get_calories_per_deer()
    { return calories_per_deer; }

    void set_calories_per_deer(int cpd)
    { calories_per_deer = cpd; }

    int get_reproductive_rate()
    { return reproductive_rate; }

    void set_reproductive_rate(int rr)
    { reproductive_rate = rr; }

    int get_min_age_to_reproduce()
    { return min_age_to_reproduce; }

    void set_min_age_to_reproduce(int mar)
    { min_age_to_reproduce = mar; }

    int get_min_calories_to_reproduce()
    { return min_calories_to_reproduce; }

    void set_min_calories_to_reproduce(int mcr)
    { min_calories_to_reproduce = mcr; }

    int get_min_calories_to_hunt()
    { return min_calories_to_hunt; }

    void set_min_calories_to_hunt(int mch)
    { min_calories_to_hunt = mch; }
};
/////////// End Predator ////////////

///////////// Factory ///////////////
class Living_Being_Factory
{
public:
    static Living_Being* create_being(char identifier)
    {
        switch(identifier)
        {
            case('g'):
            {
                Living_Being* grass = new Grass();
                return grass;
            }
            case('f'):
            {
                Living_Being* flower = new Flower();
                return flower;
            }
            case('r'):
            {
                Living_Being* rabbit = new Rabbit();
                return rabbit;
            }
            case('d'):
            {
                Living_Being* deer = new Deer();
                return deer;
            }
            case('w'):
            {
                Living_Being* wolf = new Wolf();
                return wolf;
            }
            case('b'):
            {
                Living_Being* bear = new Bear();
                return bear;
            }

            default:
            {
                cout << "FAILED SANITY CHECK in insert()" << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
};
//////////// End Factory /////////////

#endif // LIVING_BEING_H
