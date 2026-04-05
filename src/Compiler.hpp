#ifndef COMPILER_HPP
#define COMPILER_HPP

#include <SFML/Graphics.hpp>
#include "Creature.hpp"
#include "Rune.hpp"
#include "rune-types/TwistRune.hpp"
#include "rune-types/SightRune.hpp"
#include "rune-types/ChoiceRune.hpp"
#include "rune-types/WindRune.hpp"
#include "rune-types/ViolenceRune.hpp"
#include <vector>
#include <string>

class Compiler{
    public:
    static void initiallize();
    static void resolve();
    static void newCreature(Creature*);
    static std::vector <int> invTransform(std::vector <Rune>);
    static std::vector <Rune> transform(std::vector<int>, Creature*, Map&);
    static std::vector <Rune> transform(std::vector<std::vector<int>*>, Creature*, Map&);
    static std::vector <std::vector <int>*> createInstructions(std::vector <Rune>);
    
    
    private:
    static std::vector <std::vector <int>*> tempArr;
    static std::vector <Creature*> crePtrArr;
    static int step;  

};

#endif
