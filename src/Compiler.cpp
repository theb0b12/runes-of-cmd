#include "Compiler.hpp"
#include <algorithm>
#include <iostream>

// static member definitions
std::vector<std::vector<int>*> Compiler::tempArr;
std::vector<Creature*>         Compiler::crePtrArr;
int                            Compiler::step = 0;
Map*                           Compiler::areamap = nullptr;

void Compiler::initiallize(Map& m){
    areamap = &m;
    step = 0;
    crePtrArr.clear();
    // clear and rebuild tempArr cleanly
    for(auto* v : tempArr) delete v;
    tempArr.clear();
    for(int i = 0; i < 12; i++){
        tempArr.push_back(new std::vector<int>);
    }
}

void Compiler::newCreature(Creature* NC){
    crePtrArr.push_back(NC);
}

std::vector<std::unique_ptr<Rune>> Compiler::transform(std::vector<int> vec, Creature* holder, Map& map){
    std::vector<std::unique_ptr<Rune>> output;
    for(size_t i = 0; i < vec.size(); i++){
        switch(vec[i]){
            case 1: output.push_back(std::make_unique<Sight>(holder, map));            break;
            case 2: output.push_back(std::make_unique<Choice>(holder, map));           break;
            case 3: output.push_back(std::make_unique<Rune>("Harmony", holder, map));  break;
            case 4: output.push_back(std::make_unique<Rune>("Discord", holder, map));  break;
            case 5: output.push_back(std::make_unique<Wind>(holder, map));             break;
            case 6: output.push_back(std::make_unique<Twist>(holder, map));            break;
            case 7: output.push_back(std::make_unique<Violence>(holder, map));         break;
            case 8: output.push_back(std::make_unique<Rune>("\n", holder, map));       break;
        }
    }
    return output;
}

std::vector<std::unique_ptr<Rune>> Compiler::transform(std::vector<std::vector<int>*> vec, Creature* holder, Map& map){
    // find how many unique lines there are by detecting pointer repetition
    int lineNum = 1;
    while(lineNum < 12 && vec[0] != vec[lineNum]){
        lineNum++;
    }
    std::vector<int> newVec;
    for(int i = 0; i < lineNum; i++){
        for(size_t j = 0; j < vec[i]->size(); j++){
            newVec.push_back(vec[i]->at(j));
        }
        newVec.push_back(8); // newline separator
    }
    return transform(newVec, holder, map);
}

std::vector<int> Compiler::invTransform(std::vector<Rune> vec){
    std::vector<int> output;
    for(size_t i = 0; i < vec.size(); i++){
        std::string SC = vec[i].getType();
        if      (SC == "Sight")    output.push_back(1);
        else if (SC == "Choice")   output.push_back(2);
        else if (SC == "Harmony")  output.push_back(3);
        else if (SC == "Discord")  output.push_back(4);
        else if (SC == "Wind")     output.push_back(5);
        else if (SC == "Twist")    output.push_back(6);
        else if (SC == "Violence") output.push_back(7);
        else if (SC == "\n")       output.push_back(8);
    }
    return output;
}

std::vector<std::vector<int>*> Compiler::createInstructions(std::vector<Rune> runeArr){
    // clear all lines
    for(int i = 0; i < 12; i++){
        tempArr.at(i)->clear();
    }

    int lineCount = 1;
    int index = 0;
    std::vector<int> intArr = invTransform(runeArr);

    for(size_t i = 0; i < intArr.size(); i++){
        if(intArr[i] == 8){
            lineCount++;
            index++;
            if(index >= 12) break; // safety clamp
        } else {
            tempArr[index]->push_back(intArr[i]);
        }
    }

    // tile the defined lines across all 12 slots
    switch(lineCount){
        case 1:
            for(int i = 1; i < 12; i++)
                tempArr[i] = tempArr[0];
            break;
        case 2:
            for(int i = 2; i < 12; i += 2){
                tempArr[i]     = tempArr[0];
                if(i+1 < 12) tempArr[i+1] = tempArr[1];
            }
            break;
        case 3:
            for(int i = 3; i < 12; i += 3){
                tempArr[i]     = tempArr[0];
                if(i+1 < 12) tempArr[i+1] = tempArr[1];
                if(i+2 < 12) tempArr[i+2] = tempArr[2];
            }
            break;
        case 4:
            for(int i = 4; i < 12; i += 4){
                tempArr[i]     = tempArr[0];
                if(i+1 < 12) tempArr[i+1] = tempArr[1];
                if(i+2 < 12) tempArr[i+2] = tempArr[2];
                if(i+3 < 12) tempArr[i+3] = tempArr[3];
            }
            break;
        default:
            break;
    }

    return tempArr;
}

void Compiler::resolve(){
    if(crePtrArr.empty()) return;
    for(size_t i = 0; i < crePtrArr.size(); i++){
        if(crePtrArr[i]->getProgram().empty()) continue;
        for(size_t j =0; j < crePtrArr[i]->instructionArr.size(); j++){
        auto tempRune = transform(*(crePtrArr[i]->instructionArr[j]), crePtrArr[i], *areamap);
        if(tempRune.empty()) continue;
        std::vector<Rune*> pass;
        for(size_t k = 1; k < tempRune.size(); k++)
            pass.push_back(tempRune[k].get());
        tempRune[0]->activate(pass);
        }
    }
}

void Compiler::removeDeadCreatures(){
    crePtrArr.erase(
        std::remove_if(crePtrArr.begin(), crePtrArr.end(),
            [](Creature* c){ return c->isDead(); }),
        crePtrArr.end()
    );
}