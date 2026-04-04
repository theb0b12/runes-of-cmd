#ifndef WIND_HPP
#define WIND_HPP
#include "../Rune.hpp"

class Wind :public Rune{
    public:
        Wind(Creature* h, Map& map); 
        int activate(std::vector<Rune*>) override; //override the pure virtual function from the base class
};

#endif