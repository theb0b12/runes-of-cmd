#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player {
    public:
        Player();
        float getXpos();
        float getYpos();
        int getFacing();
        void moveBy(float, float);
    private:
        float xPos;
        float yPos;
        int isFacing;
};


#endif