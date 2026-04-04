#ifndef VIOLENCE_HPP
#define VIOLENCE_HPP
#include "Rune.hpp"

class Violence :public Rune{
    public:
        Violence(Creature* h); 
        int activate(std::vector<Rune*>) override; //override the pure virtual function from the base class
};

#endif