#ifndef CREATURE_HPP
#define CREATURE_HPP

class creature {
public:
    creature();
    float getXpos();
    float getYpos();
    int getHealth();
    void moveBy(float, float);
private:
    
    float xPos;
    float yPos;
    int health;
};

#endif