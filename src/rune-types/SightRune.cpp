#include "SightRune.hpp"

Sight::Sight(Creature* h) : Rune("Sight", h){}

int Sight::activate(std::vector<Rune*> r){
    if(r.empty() || (r[0]->getType() != "Harmony" && r[0]->getType() != "Discord")){
        //if no follow-up rune is provided, or it is not a valid rune, return error code
        return -1;
    } if(r[0]->getType() == "Harmony" && getHolder()->inFront() == 1){
        //if the follow-up rune is a Harmony rune, return a value indicating the creature can see an ally in front of it
        return 1;
    } else if (r[0]->getType() == "Discord" && getHolder()->inFront() == -1){
        //if the follow-up rune is a Discord rune, return a value indicating the creature can see an enemy in front of it
        return 1;
    }
    return 0;
}