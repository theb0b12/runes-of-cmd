#include "Player.hpp"


//constructor, there is no destructor or copy constructor as there is always only one player 
Player::Player(){
    xPos = 0;
    yPos = 0;
    isFacing = 1;
    body = sf::CircleShape(50);
    
}

void Player::printPlayer(sf::RenderWindow& window){
    body.setPosition({xPos,yPos});
    window.draw(body);
}

//getters
float Player::getXpos(){
    return xPos;
}

float Player::getYpos(){
    return yPos;
}

int Player::getFacing(){
    return isFacing;
}

// player moves then faces the direction the player is moving in
void Player::moveBy(float x, float y, float dt){
    xPos += x * _speed * dt;
    yPos += y * _speed * dt;

    if (x > 0) isFacing = 1;
    else if (x < 0) isFacing = -1;

    if (y > 0) isFacing = 2;
    else if (y < 0) isFacing = -2;
}

void Player::setSpeed(float speed){
    _speed = speed;
}