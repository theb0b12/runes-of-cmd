#include "player.hpp"

//constructor, there is no destructor or copy constructor as there is always only one player 
player::player(){
    xPos = 0;
    yPos = 0;
    isFacing = 1;
}

//getters
float player::getXpos(){
    return xPos;
}

float player::getYpos(){
    return yPos;
}

int player::getFacing(){
    return isFacing;
}

//player moves then faces the direction the player is moving in
void player::moveBy(float x, float y){
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

