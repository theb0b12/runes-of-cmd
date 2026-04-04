#include "Creature.hpp"
//constructor
creature::creature(float x, float y, int hp){
    xPos = x;
    yPos = y;
    health = hp;
    isFacing = -1;
}

//getters
float creature::getXpos(){
    return xPos;
}

float creature::getYpos(){
    return yPos;
}

int creature::getHealth(){
    return health;
}

int creature::getFacing(){
    return isFacing;
}

//creature moves then faces the direction the creature is moving in
void creature::moveBy(float x, float y){
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