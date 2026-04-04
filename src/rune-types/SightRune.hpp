#ifndef SIGHTRUNE_HPP
#define SIGHTRUNE_HPP
#include "../Rune.hpp"

class Sight :public Rune{
    public:
        Sight(Creature* h);
        int activate(std::vector<Rune*>) override; //override the pure virtual function from the base class
};

#endif