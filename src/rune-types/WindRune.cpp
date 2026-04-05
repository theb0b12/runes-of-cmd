#include "WindRune.hpp"

Wind::Wind(Creature* h, Map& map) : Rune("Wind", h, map){}

int Wind::activate(std::vector<Rune*> r){
    if(!r.empty() && r[0]->getType() != "\n") return -1;
    Creature* holder = getHolder();
    int facing = holder->getFacing();
    int oldX = holder->getXpos();
    int oldY = holder->getYpos();

    switch(facing){
        case  1: holder->moveBy( 1,  0, map); break;
        case -1: holder->moveBy(-1,  0, map); break;
        case  2: holder->moveBy( 0, -1, map); break;
        case -2: holder->moveBy( 0,  1, map); break;
    }

    // // hit a wall — reverse direction
    // if(holder->getXpos() == oldX && holder->getYpos() == oldY){
    //     holder->setFacing(-facing);
    // }
    return 1;
}