#include "ChoiceRune.hpp"

Choice::Choice(Creature* h) : Rune("Choice", h){}

int Choice::activate(std::vector<Rune*> r){
    if(r.empty() || r[0]->getType() != "Sight"){
        //if no follow-up rune is provided, or it is not a valid rune, return error code
        return -1;
    } 
    return r[0]->activate(std::vector<Rune*>(r.begin() + 1, r.end())); //return a value indicating the result of the activation
}