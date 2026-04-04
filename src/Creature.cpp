#include "Creature.hpp"

//constructor
Creature::Creature(float x, float y, int hp, bool enemy){
    xPos = x;
    yPos = y;
    health = hp;
    isFacing = -1;
    isEnemy = enemy;
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
}

//Add a rune to the creature's possible runes
void Creature::addRune(Rune r){
    possibleRunes.push_back(r);
}

//Check if there is an enemy in front of the creature
int Creature::inFront(){

//check if there is an object in front of the creature and wheather it is an enemy
return 0;
}

void Creature::attack(){
    //attack regardless of whether there is an enemy in front or not
    //to be implemented
}