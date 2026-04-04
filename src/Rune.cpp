#include "Rune.hpp"

//Types can only be: "Sight", "Choice", "Harmony", "Discord", "Wind", "Twist", "Violence"
Rune::Rune(std::string t, Creature* h, Map& m)
    : type(t), holder(h), map(m) {
}

int Rune::activate(std::vector<Rune*> r){
    //base class implementation of activate, can be overridden by derived classes
    return 0;
}