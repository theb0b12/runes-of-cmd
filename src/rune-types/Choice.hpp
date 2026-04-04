#ifndef CHOICE_HPP
#define CHOICE_HPP
#include "Rune.hpp"

class Choice :public Rune{
    public:
        Choice();
        int activate(Rune*) override; //override the pure virtual function from the base class
};

#endif