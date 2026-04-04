#ifndef CHOICE_HPP
#define CHOICE_HPP
#include "../Rune.hpp"

class Choice :public Rune{
    public:
        Choice(Creature* h, Map& map); 
        int activate(std::vector<Rune*>) override; //override the pure virtual function from the base class
};

#endif