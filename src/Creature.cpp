#include "Creature.hpp"
#include <iostream>
#include <algorithm>

//constructor
Creature::Creature(int x, int y, int hp, bool enemy, int count){
    xPos = x;
    if(xPos > 11)
        xPos = 11;
    if(xPos < 0)
        xPos = 0;
    yPos = y;
    if(yPos > 5)
        yPos = 5;
    if(yPos < 0)
        yPos = 0;
    health = hp;
    isFacing = -1;
    isEnemy = enemy;
    possibleRunes = std::vector<int>();
    body = sf::CircleShape(50);
    id = count;
    if(id % 2 == 0){
        body.setFillColor(sf::Color::Blue);
    } else {
        body.setFillColor(sf::Color::Red);
    }

    for(int i = 0; i < 12; i++){
        std::vector<int>* tempvec = new std::vector<int>();
        tempvec->push_back(1);
        instructionArr.push_back(tempvec);
    }

    if(isEnemy) {
        _anim = Animation("assets/badGuy", 4.f);
    } else {
        _anim = Animation("assets/goodGuy", 4.f);
    }
    _anim.setScale({ 9.f, 9.f });

    
}

//getters
int Creature::getXpos(){
    return xPos;
}

int Creature::getYpos(){
    return yPos;
}

int Creature::getHealth(){
    return health;
}

int Creature::getFacing(){
    return isFacing;
}

bool Creature::getEnemy(){
    return isEnemy;
}

//creature moves then faces the direction the creature is moving in
void Creature::moveBy(int x, int y){
    // std::cout << "Moving creature " << id << " from " << xPos << "," << yPos;
    xPos += x;
    yPos += y;
    if(xPos > 11) xPos = 11;
    if(xPos < 0)  xPos = 0;
    if(yPos > 5)  yPos = 5;
    if(yPos < 0)  yPos = 0;
    // std::cout << " to " << xPos << "," << yPos << " (ptr: " << this << ")" << std::endl;
}

//Add a rune to the creature's possible runes
void Creature::addRune(int r){
    possibleRunes.push_back(r);
}


void Creature::drawCreature(sf::RenderWindow& window, Map& map){
    // std::cout << "drawing creature " << id << " at " << xPos << "," << yPos << " (ptr: " << this << ")" << std::endl;
    float px = xPos * map.getTileWidth() + (map.getWidth() * 0.3f)/0.7f;
    float py = (yPos - 3) * map.getTileHeight() + map.getHeight()/2;
    _anim.setPosition({ px, py });
    _anim.update(0.016f); // fixed timestep ~60fps
    window.draw(_anim.getSprite());
    map.occupied[xPos][yPos] = id;
}

//Check if there is an enemy in front of the creature, returns id of creature if found and 0 if empty
int Creature::inFront(Map& map){
    if(isFacing == 2){
        if(yPos == 0)
            return 0;
        else
            return map.occupied[xPos][yPos-1];
    }
    if(isFacing == -2){
        if(yPos == 6)
            return 0;
        else
            return map.occupied[xPos][yPos+1];
    }
    if(isFacing == 1){
        if(xPos == 12)
            return 0;
        else
            return map.occupied[xPos+1][yPos];
    }
    if(isFacing == -1){
        if(xPos == 0)
            return 0;
        else
            return map.occupied[xPos-1][yPos];
    }

    //check if there is an object in front of the creature and wheather it is an enemy
    return 0;
}

int Creature::getId() const{
    return id;
}


void Creature::attack(Creature* target){
    if(!target) return;
    target->takeDamage(1);
}


std::vector<Creature*> Creature::_registry;

std::vector<Creature*>& Creature::getRegistry() { return _registry; }

void Creature::registerCreature(Creature* c) {
    _registry.push_back(c);
}

void Creature::unregisterCreature(Creature* c) {
    _registry.erase(
        std::remove(_registry.begin(), _registry.end(), c),
        _registry.end()
    );
}