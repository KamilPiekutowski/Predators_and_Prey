#include "Living_Being.h"
#include <iostream>
using namespace std;

Living_Being::Living_Being()
{
    identifier = ' ';
}

Living_Being::~Living_Being()
{
    //dtor
}

char Living_Being::getIdentifier(){
    return identifier;
}

void Living_Being::take_turn()
{
    //cout << "Inside animal turn..." << endl;
}

