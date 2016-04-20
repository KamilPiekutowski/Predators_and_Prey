#include "Square.h"

Square::Square()
{
    p_id = ' ';
    a_id = ' ';
}

Square::~Square()
{
    //dtor
}

Living_Being* Square::get_animal()
{ return animal; }

void Square::set_animal(Living_Being *an)
{ animal = an; }

void Square::set_plant(Living_Being* p)
{ plant = p;}

Living_Being* Square::get_plant()
{ return plant; }

void Square::set_identifier(char c)
{ }//identifier = c; }

char Square::get_identifier()
{ return ' ';} /*identifier;*/
