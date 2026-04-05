#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "Map.hpp"
#include <vector>

class Creature {
public:
    Creature(int, int, int, bool, int);
    int getXpos();
    int getYpos();
    int getFacing();
    int getHealth();
    int inFront(Map& map);
    bool getEnemy();
    void attack();
    void moveBy(int, int);
    void setFacing(int f) { isFacing = f; }
    void addRune(int);
    void drawCreature(sf::RenderWindow&, Map&);
    int getId() const;

    void setProgram(std::vector<int> prog) { program = prog; }
    std::vector<int> getProgram() const { return program; }

    std::vector <std::vector <int>*> instructionArr;
private:
    std::vector <int> possibleRunes;
    sf::CircleShape body;
    bool isEnemy;
    int isFacing;
    int xPos;
    int yPos;
    int health;
    int id;

    std::vector<int> program;
};

#endif