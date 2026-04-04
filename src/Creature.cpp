class creature {
public:
    creature(float, float, int);
    float getXpos();
    float getYpos();
    int getHealth();
    void moveBy(float, float);
private:

    float xPos;
    float yPos;
    int health;
};

creature::creature(float x, float y, int hp){
    xPos = x;
    yPos = y;
    health = hp;
}