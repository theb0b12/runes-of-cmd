#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "Map.hpp"
#include "Animation.hpp"
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
    void moveBy(int, int, Map&);
    void setFacing(int f) { isFacing = f; }
    void addRune(int);
    void drawCreature(sf::RenderWindow&, Map&);
    int getId() const;

    void setProgram(std::vector<int> prog) { program = prog; }
    std::vector<int> getProgram() const { return program; }


    bool isDead() const { return health <= 0; }
    void takeDamage(int dmg) { health -= dmg; }

    void attack(Creature* target);

    static std::vector<Creature*>& getRegistry();
    static void registerCreature(Creature* c);
    static void unregisterCreature(Creature* c);

    void rotateAnim90();
    

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

    Animation _anim;

    static std::vector<Creature*> _registry;
    
    float _rotation = 0.f;
};

#endif