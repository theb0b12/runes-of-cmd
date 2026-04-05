#include "ViolenceRune.hpp"

Violence::Violence(Creature* h, Map& map) : Rune("Violence", h, map){}

int Violence::activate(std::vector<Rune*> r){
    if(!r.empty() && r[0]->getType() != "\n") return -1;
    Creature* holder = getHolder();
    int targetId = holder->inFront(map);
    if(targetId == 0) return 0;
    for(Creature* c : Creature::getRegistry()){
        if(c->getId() == targetId){
            holder->attack(c);
            std::cout << "Violence: hit id " << targetId << " health now: " << c->getHealth() << "\n";
            if(c->isDead()){
                Creature::unregisterCreature(c);
            }
            return 1;
        }
    }
    return 0;
}