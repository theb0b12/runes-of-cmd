#include "Rune.hpp"

//Types can only be: "Sight", "Choice", "Harmony", "Discord"
Rune::Rune(std::string t, Creature* h) {
    type = t;
    holder = h;
}

int Rune::activate(std::vector<Rune*> r){
    //base class implementation of activate, can be overridden by derived classes
    return 0;
}