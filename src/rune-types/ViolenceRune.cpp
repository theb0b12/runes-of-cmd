#include "ViolenceRune.hpp"

Violence::Violence(Creature* h, Map& map) : Rune("Violence", h, map){}

int Violence::activate(std::vector<Rune*> r){
    if(!r.empty()){
        //if any follow-up runes are provided, return error code since Violence should not have any follow-up runes
        return -1;
    } 
    getHolder()->attack();
    return 0; 
}