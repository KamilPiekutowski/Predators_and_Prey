#ifndef SQUARE_H
#define SQUARE_H
#include "TILE.h"
#include "Living_Being.h"

class Square
{
private:

    Living_Being* plant;
    Living_Being* animal;


public:
    Square();
    ~Square();

    // getters / setters
    Living_Being* get_animal();
    void set_animal(Living_Being*);
    void set_plant(Living_Being* p);
    Living_Being* get_plant();
    void set_identifier(char);
    char get_identifier();
    char p_id;
    char a_id;

    TILE tile;
    /*
    void set_empty(bool e)
    { empty = e; }

    bool get_empty()
    { return empty; }

    void set_grass(bool g)
    { grass = g; }

    bool get_grass()
    { return grass; }

    void set_flower(bool f)
    { flower = f;}

    bool get_flower()
    { return flower; }

    void set_rabbit(bool r)
    { rabbit = r; }

    bool get_rabbit()
    { return rabbit; }

    void set_deer(bool d)
    { deer = d; }

    bool get_deer()
    { return deer; }

    void set_wolf(bool w)
    { wolf = w; }

    bool get_wolf()
    { return wolf; }

    void set_bear(bool b)
    { bear = b; }

    bool get_bear()
    { return bear; }

    void set_grass_rabbit(bool gr)
    { grass_rabbit = gr; }

    bool get_grass_rabbit()
    { return grass_rabbit; }

    void set_grass_deer(bool gd)
    { grass_deer = gd;}

    bool get_grass_deer()
    { return grass_deer;}

    void set_grass_wolf(bool gw)
    { grass_wolf = gw; }

    bool get_grass_wolf()
    { return grass_wolf;}

    void set_grass_bear(bool gb)
    { grass_bear = gb; }

    bool get_grass_bear()
    { return grass_bear; }

    void set_flower_rabbit(bool fr)
    { flower_rabbit = fr; }

    bool get_flower_rabbit()
    { return flower_rabbit; }

    void set_flower_deer(bool fd)
    { flower_deer = fd;}

    bool get_flower_deer()
    { return flower_deer; }

    void set_flower_wolf(bool fw)
    { flower_wolf = fw; }

    bool get_flower_wolf()
    { return flower_wolf; }

    void set_flower_bear(bool fb)
    { flower_bear = fb; }

    bool get_flower_bear()
    { return flower_bear;}
    */
};

#endif // SQUARE_H
