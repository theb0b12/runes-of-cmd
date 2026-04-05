#include "SightRune.hpp"

Sight::Sight(Creature* h, Map& map) : Rune("Sight", h, map){}

int Sight::activate(std::vector<Rune*> r){
    if(r.empty()) return -1;
    std::string modifier = r[0]->getType();
    int targetId = getHolder()->inFront(map);
    if(targetId == 0) return 0; // nothing in front
    if(modifier == "Discord"){
        // true if enemy in front (odd id)
        return targetId % 2 == 1 ? 1 : 0;
    }
    if(modifier == "Harmony"){
        // true if ally in front (even id)
        return targetId % 2 == 0 ? 1 : 0;
    }
    return -1;
}