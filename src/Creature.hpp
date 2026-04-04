#ifndef CREATURE_HPP
#define CREATURE_HPP

class creature {
public:
    creature(float, float, int);
    float getXpos();
    float getYpos();
    int getFacing();
    int getHealth();
    void moveBy(float, float);
private:
    int isFacing;
    float xPos;
    float yPos;
    int health;
};

#endif