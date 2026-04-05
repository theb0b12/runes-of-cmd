#ifndef COMPILER_HPP
#define COMPILER_HPP

#include <SFML/Graphics.hpp>
#include "Creature.hpp"
#include "Rune.hpp"
#include <vector>
#include <string>

class Compiler{
    public:
    static void initiallize();
    static void resolve();
    static void newCreature(Creature*);
    static std::vector <int> invTransform(std::vector <Rune>);
    static std::vector <std::vector <int>*> createInstructions(std::vector <Rune>);
    
    private:
    static std::vector <std::vector <int>*> tempArr;
    static std::vector <Creature*> crePtrArr;
    static int step;  

};

#endif
