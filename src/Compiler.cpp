#include "Compiler.hpp"
#include <algorithm>
#include <iostream>

std::vector<Compiler::CreatureProgram> Compiler::_creatures;
Map* Compiler::_map = nullptr;

void Compiler::initialize(Map& m){
    _map = &m;
    _creatures.clear();
}

void Compiler::registerCreature(Creature* c){
    for(auto& cp : _creatures)
        if(cp.creature == c) return;
    CreatureProgram cp;
    cp.creature = c;
    cp.step     = 0;
    _creatures.push_back(cp);
}

void Compiler::removeDeadCreatures(){
    _creatures.erase(
        std::remove_if(_creatures.begin(), _creatures.end(),
            [](const CreatureProgram& cp){ return cp.creature->isDead(); }),
        _creatures.end()
    );
}

void Compiler::setProgram(Creature* c, std::vector<int> program){
    std::vector<std::vector<int>> lines;
    std::vector<int> current;
    for(int x : program){
        if(x == 8){
            if(!current.empty()){
                lines.push_back(current);
                current.clear();
            }
        } else {
            current.push_back(x);
        }
    }
    if(!current.empty()) lines.push_back(current);

    for(auto& cp : _creatures){
        if(cp.creature == c){
            cp.lines = lines;
            cp.step  = 0;
            return;
        }
    }
    CreatureProgram cp;
    cp.creature = c;
    cp.lines    = lines;
    cp.step     = 0;
    _creatures.push_back(cp);
}

void Compiler::resolve(){
    if(!_map) return;
    for(auto& cp : _creatures){
        if(cp.lines.empty()) continue;

        int lineIdx = cp.step % (int)cp.lines.size();
        auto& line  = cp.lines[lineIdx];
        if(line.empty()){
            cp.step = (cp.step + 1) % (int)cp.lines.size();
            continue;
        }

        // build all runes for this line
        auto runes = transform(line, cp.creature, *_map);
        if(runes.empty()) continue;

        // first rune is the verb, rest are its arguments
        std::vector<Rune*> pass;
        for(size_t j = 1; j < runes.size(); j++)
            pass.push_back(runes[j].get());

        runes[0]->activate(pass);

        // advance to next line
        cp.step = (cp.step + 1) % (int)cp.lines.size();
    }
}

std::vector<std::unique_ptr<Rune>> Compiler::transform(std::vector<int> vec, Creature* holder, Map& map){
    std::vector<std::unique_ptr<Rune>> output;
    for(int x : vec){
        switch(x){
            case 1: output.push_back(std::make_unique<Sight>(holder, map));            break;
            case 2: output.push_back(std::make_unique<Choice>(holder, map));           break;
            case 3: output.push_back(std::make_unique<Rune>("Harmony", holder, map));  break;
            case 4: output.push_back(std::make_unique<Rune>("Discord", holder, map));  break;
            case 5: output.push_back(std::make_unique<Wind>(holder, map));             break;
            case 6: output.push_back(std::make_unique<Twist>(holder, map));            break;
            case 7: output.push_back(std::make_unique<Violence>(holder, map));         break;
        }
    }
    return output;
}

std::vector<int> Compiler::invTransform(std::vector<Rune> vec){
    std::vector<int> output;
    for(auto& r : vec){
        std::string t = r.getType();
        if (t == "Sight") output.push_back(1);
        else if (t == "Choice") output.push_back(2);
        else if (t == "Harmony") output.push_back(3);
        else if (t == "Discord") output.push_back(4);
        else if (t == "Wind") output.push_back(5);
        else if (t == "Twist") output.push_back(6);
        else if (t == "Violence") output.push_back(7);
        else if (t == "Escape") output.push_back(8);
    }
    return output;
}