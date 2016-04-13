#ifndef LIVING_BEING_H
#define LIVING_BEING_H


class Living_Being
{
private:


public:
    virtual void eat(int) = 0;
    virtual void die() = 0;
    virtual void take_turn() = 0;
    virtual char getIdentifier();


    Living_Being();
    ~Living_Being();

    char identifier;
};

class Mammal : public Living_Being
{
    virtual void die()       = 0;
    virtual void hunger()    = 0;
    virtual void move()      = 0;
    virtual void reproduce() = 0;
    virtual void eat(int)       = 0;
    virtual void take_turn() = 0;

};

class Prey : public Mammal
{
    virtual void evade()      = 0;
    virtual void eat(int)        = 0;
    virtual void take_turn()  = 0;
    virtual void age()        = 0;
};

class Predator : public Mammal
{
    virtual void hunt() = 0;
    virtual void take_turn() = 0;
};





#endif // LIVING_BEING_H
