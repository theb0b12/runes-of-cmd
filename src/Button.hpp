#pragma once

#include <SFML/Graphics.hpp>

class Button{
    public:
        Button(sf::RectangleShape* button);
        void virtual update(sf::Vector2f mousePos);

        // getters
        bool getToggle() const;

        // setters 
        void setToggle(bool value);

    protected:
        sf::RectangleShape* button;
        bool mousePressed;
        bool pressedInside;

        bool toggle;
        virtual bool canToggle() const;
};