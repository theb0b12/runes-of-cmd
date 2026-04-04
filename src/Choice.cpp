#include "Rune.hpp"
#include "Choice.hpp"

Choice::Choice() : Rune("Choice"){}

int Choice::activate(Rune* r){
    if(r == nullptr || r->getType() != "Sight"){
        //if no follow-up rune is provided, or it is not a valid rune, return error code
        return -1;
    } 
    return 0; //return a value indicating the result of the activation
}