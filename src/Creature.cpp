#include "Creature.hpp"

//constructor
Creature::Creature(float x, float y, int hp){
    xPos = x;
    yPos = y;
    health = hp;
    isFacing = -1;
    possibleRunes = std::vector<Rune>();
}

//getters
float Creature::getXpos(){
    return xPos;
}

float Creature::getYpos(){
    return yPos;
}

int Creature::getHealth(){
    return health;
}

int Creature::getFacing(){
    return isFacing;
}

//creature moves then faces the direction the creature is moving in
void Creature::moveBy(float x, float y){
    xPos += x;
    yPos += y;
    if(x > 0){
        isFacing = 1;
    }
    else if(x < 0){
        isFacing = -1;
    }
    
    if(y > 0){
        isFacing = 2;
    }
    else if(y < 0){
        isFacing = -2;
    }
}

//Add a rune to the creature's possible runes
void Creature::addRune(Rune r){
    possibleRunes.push_back(r);
}