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
        const sf::RectangleShape& getSprite() const { return sprite; }
        sf::RectangleShape& getSprite() { return sprite; }
        void initSprite(); // call after construction to set placeholder color
        Map& map;


    private:
        std::string type;
        Creature * holder; //pointer to the creature that holds the rune, can be nullptr if not held by any creature
        sf::RectangleShape sprite; // 64x64 placeholder, swap for sf::Sprite later
};

#endif
