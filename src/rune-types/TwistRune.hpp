#ifndef TWIST_HPP
#define TWIST_HPP
#include "../Rune.hpp"

class Twist :public Rune{
    public:
        Twist(Creature* h); 
        int activate(std::vector<Rune*>) override; //override the pure virtual function from the base class
};

#endif