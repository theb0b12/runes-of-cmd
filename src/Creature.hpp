#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "Rune.hpp"
#include <vector>

class Creature {
public:
    Creature(float, float, int, bool);
    float getXpos();
    float getYpos();
    int getFacing();
    int getHealth();
    int inFront();
    void attack();
    void moveBy(float, float);
    void setFacing(int f) { isFacing = f; }
    void addRune(Rune);
private:
    std::vector <Rune> possibleRunes;
    bool isEnemy;
    int isFacing;
    float xPos;
    float yPos;
    int health;
};

#endif