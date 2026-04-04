#include "WindRune.hpp"

Wind::Wind(Creature* h) : Rune("Wind", h){}

int Wind::activate(std::vector<Rune*> r){
    if(!r.empty()){
        //if any follow-up runes are provided, return error code since Wind should not have any follow-up runes
        return -1;
    } 
        Creature* holder = getHolder();
        int facing = holder->getFacing();

        switch(facing){
            case 1: //facing right
                holder->moveBy(1.0, 0);
                break;
            case -1: //facing left
                holder->moveBy(-1.0, 0);
                break;
            case 2: //facing up
                holder->moveBy(0, 1.0); //move up
                break;
            case -2: //facing down
                holder->moveBy(0, -1.0); //move down
                break;
        }
    return 0;
}