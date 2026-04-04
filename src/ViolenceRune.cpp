#include "ViolenceRune.hpp"

Violence::Violence(Creature* h) : Rune("Violence", h){}

int Violence::activate(std::vector<Rune*> r){
    if(!r.empty()){
        //if any follow-up runes are provided, return error code since Violence should not have any follow-up runes
        return -1;
    } 
    getHolder()->attack(); //call the attack function of the creature that holds the rune
    return 0; //return a value indicating the result of the activation
}