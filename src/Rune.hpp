#ifndef RUNE_HPP
#define RUNE_HPP
#include <string>
#include <vector>
#include "Creature.hpp"
#include "Map.hpp"

class Rune{
    public:


        Rune(std::string, Creature*, Map&);
        std::string getType() const { return type; }
        virtual int  activate(std::vector<Rune*>); //pure virtual function to be implemented by derived classes
        Creature* getHolder() const { return holder; }
        Map& map;
    private:
        std::string type;
        Creature * holder; //pointer to the creature that holds the rune, can be nullptr if not held by any creature
};

#endif
