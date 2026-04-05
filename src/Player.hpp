#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Map.hpp"

class Player {
    public:
        Player(Map&);
        float getXpos();
        float getYpos();
        int getXTile();
        int getYTile();
        void printPlayer(sf::RenderWindow&);
        int getFacing();
        void moveBy(float, float, float);

        void setSpeed(float);

        sf::Vector2f getPosition() const;
        
    private:
        Map& map;
        float xPos;
        int xTile;
        float yPos;
        int yTile;
        int isFacing;
        sf::CircleShape body;

        float _speed = 10.f;
};


#endif