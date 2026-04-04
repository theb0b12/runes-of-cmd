#include "TwistRune.hpp"

Twist::Twist(Creature* h, Map& map) : Rune("Twist", h, map){}

int Twist::activate(std::vector<Rune*> r){
    if(!r.empty()){
        //if any follow-up runes are provided, return error code since Twist should not have any follow-up runes
        return -1;
    } 
    //Creature turns 90 degrees to the right, so the direction it is facing changes accordingly
        Creature* holder = getHolder();
        int facing = holder->getFacing();
    
        switch(facing){
            case 1: //facing right
                holder->setFacing(-2); //now facing down
                break;
            case -1: //facing left
                holder->setFacing(2); //now facing up
                break;
            case 2: //facing up
                holder->setFacing(1); //now facing right
                break;
            case -2: //facing down
                holder->setFacing(-1); //now facing left   
                break;
        }
    return 0;
}