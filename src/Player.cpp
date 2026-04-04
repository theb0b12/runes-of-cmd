#include "Player.hpp"


//constructor, there is no destructor or copy constructor as there is always only one player 
Player::Player(Map& m) : map(m){
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

int Player::getXTile(){
    return xTile;
}

int Player::getYTile(){
    return yTile;
}

int Player::getFacing(){
    return isFacing;
}

// player moves then faces the direction the player is moving in
void Player::moveBy(float x, float y, float dt){
    xPos += x * _speed * dt;
    if(xPos > map.getWidth()/0.7f - 100)
        xPos = map.getWidth()/0.7f - 100;
    if(xPos < (0.3f*map.getWidth())/0.7f)
        xPos = (0.3f*map.getWidth())/0.7f;
    yPos += y * _speed * dt;

    if(yPos < ((map.getHeight() - (map.getTileHeight() * 6))/6) * 3)
        yPos = ((map.getHeight() - (map.getTileHeight() * 6))/6) * 3;
    if(yPos > map.getHeight()/2 + (map.getTileHeight() * 3) - 100)
        yPos = map.getHeight()/2 + (map.getTileHeight() * 3) - 100;

    if (x > 0) isFacing = 1;
    else if (x < 0) isFacing = -1;

    if (y > 0) isFacing = 2;
    else if (y < 0) isFacing = -2;

    xTile = (xPos + 50 - (0.3f*map.getWidth())/0.7f)/map.getTileWidth();
    yTile = (yPos + 50 - ((map.getHeight() - (map.getTileHeight() * 6))/6) * 3)/map.getTileHeight();
}

void Player::setSpeed(float speed){
    _speed = speed;
}