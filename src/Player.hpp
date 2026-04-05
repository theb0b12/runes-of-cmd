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

        static constexpr float SPRITE_HALF_W = 120.f; // 96 * 2.5 / 2
        static constexpr float SPRITE_HALF_H = 105.f; // 84 * 2.5 / 2
};


#endif