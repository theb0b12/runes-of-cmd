#ifndef CREATURE_HPP
#define CREATURE_HPP
#include "Rune.hpp"
#include <vector>

class Creature {
public:
    Creature(float, float, int);
    float getXpos();
    float getYpos();
    int getFacing();
    int getHealth();
    void moveBy(float, float);
    void addRune(Rune);
private:
    std::vector <Rune> possibleRunes;
    int isFacing;
    float xPos;
    float yPos;
    int health;
};

#endif