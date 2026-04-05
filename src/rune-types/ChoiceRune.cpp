#include "ChoiceRune.hpp"

Choice::Choice(Creature* h, Map& map) : Rune("Choice", h, map){}

int Choice::activate(std::vector<Rune*> r){
    if(r.empty() || r[0]->getType() != "Sight") return -1;
    
    // pass everything after Sight to Sight's activate
    std::vector<Rune*> sightArgs(r.begin() + 1, r.end());
    int condition = r[0]->activate(sightArgs);
    
    if(condition == 1){
        // sightArgs[0] = Harmony/Discord (modifier)
        // sightArgs[1] = action rune (Violence/Wind/etc)
        if(sightArgs.size() > 1){
            std::vector<Rune*> actionArgs(sightArgs.begin() + 2, sightArgs.end());
            return sightArgs[1]->activate(actionArgs);
        }
    }
    return 0;
}