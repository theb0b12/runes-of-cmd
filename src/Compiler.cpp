#include "Compiler.hpp"

void Compiler::initiallize(){
    step = 0;
    crePtrArr.clear();
    for(int i = 0; i < 12; i++){
        tempArr.push_back(new std::vector <int>);
    }
    
}

void Compiler::newCreature(Creature* NC){
    crePtrArr.push_back(NC);
}

std::vector <int> invTransform(std::vector <Rune> vec){
    std::vector <int> output;
    for(size_t i = 0; i < vec.size(); i++ ){
        std::string SC = vec[i].getType();
        if (SC == "Sight") {
            output.push_back(1);
        }
        else if (SC == "Choice") {
            output.push_back(2);
        }
        else if (SC == "Harmony") {
            output.push_back(3);
        }
        else if (SC == "Discord") {
            output.push_back(4);
        }
        else if (SC == "Wind") {
            output.push_back(5);
        }
        else if (SC == "Twist") {
            output.push_back(6);
        }
        else if (SC == "Violence") {
            output.push_back(7);
        }
        else if (SC == "\n") {
            output.push_back(8);
        }
    }

    return output;
}


std::vector <std::vector <int>*> Compiler::createInstructions(std::vector <Rune> runeArr){
    for(int i = 0; i < 12; i++){
        tempArr.at(i)->clear();
    }
    int lineCount = 1;
    int index= 0;
    std::vector <int> intArr = invTransform(runeArr);
    for(size_t i = 0; i < intArr.size(); i++){
        if(intArr[i] == 8){
            lineCount++;
            index++;
        }else{
            tempArr[index]->push_back(intArr[i]);
        }
    }

    switch (lineCount){
    case 1:
        for(int i = 1; i < 12; i++){
            tempArr[i] = tempArr[0];
        }
        break;
    case 2:
        for(int i = 2; i < 12; i += 2){
            tempArr[i] = tempArr[0];
            tempArr[i + 1] = tempArr[1];
        }
    case 3:
        for(int i = 3; i < 12; i += 3){
            tempArr[i] = tempArr[0];
            tempArr[i + 1] = tempArr[1];
            tempArr[i + 2] = tempArr[2];
        }
    case 4:
        for(int i = 4; i < 12; i += 4){
            tempArr[i] = tempArr[0];
            tempArr[i + 1] = tempArr[1];
            tempArr[i + 2] = tempArr[2];
            tempArr[i + 3] = tempArr[3];
        }
    default:
        break;
    }

    return tempArr;

}
