#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Player {
    public:
        Player();
        float getXpos();
        float getYpos();
        void printPlayer(sf::RenderWindow&);
        int getFacing();
        void moveBy(float, float);
    private:
        float xPos;
        float yPos;
        int isFacing;
        sf::CircleShape body;
};


#endif