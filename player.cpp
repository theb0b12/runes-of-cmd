class player {
    public:
        player();
        float getXpos();
        float getYpos();
        int getFacing();
        void moveBy(float x, float y);
    private:
        float xPos;
        float yPos;
        //1 is right, -1 is left, 2 is down, -2 is up
        int isFacing;
};

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

