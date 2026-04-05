#include "TwistRune.hpp"

Twist::Twist(Creature* h, Map& map) : Rune("Twist", h, map){}

int Twist::activate(std::vector<Rune*> r)
{
    if (!r.empty() && r[0]->getType() != "\n")
        return -1;

    Creature* holder = getHolder();
    int facing = holder->getFacing();

    switch (facing) {
        case  1: holder->setFacing(-2); break;
        case -1: holder->setFacing( 2); break;
        case  2: holder->setFacing( 1); break;
        case -2: holder->setFacing(-1); break;
    }

    holder->rotateAnim90();

    return 0;
}