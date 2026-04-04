#include "Rune.hpp"


Rune::Rune(std::string t){
    type = t;
}

int Rune::activate(Rune* r){
    //base class implementation of activate, can be overridden by derived classes
    return 0;
}