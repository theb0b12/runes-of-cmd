#pragma once
#include <vector>
#include <memory>
#include "Creature.hpp"
#include "Rune.hpp"
#include "Map.hpp"
#include "rune-types/SightRune.hpp"
#include "rune-types/ChoiceRune.hpp"
#include "rune-types/WindRune.hpp"
#include "rune-types/TwistRune.hpp"
#include "rune-types/ViolenceRune.hpp"

class Compiler {
public:
    static void initialize(Map& m);
    static void registerCreature(Creature* c);
    static void removeDeadCreatures();
    static void setProgram(Creature* c, std::vector<int> program);
    static void resolve();
    static std::vector<std::unique_ptr<Rune>> transform(std::vector<int> vec, Creature* holder, Map& map);
    static std::vector<int> invTransform(std::vector<Rune> vec);
    static bool hasCreatures() { return !_creatures.empty(); }

private:
    struct CreatureProgram {
        Creature*                     creature;
        std::vector<std::vector<int>> lines;
        int                           step = 0;
    };
    static std::vector<CreatureProgram> _creatures;
    static Map* _map;
};