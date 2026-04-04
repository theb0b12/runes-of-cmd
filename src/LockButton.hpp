#pragma once
#include "Button.hpp"
#include <SFML/Graphics.hpp>

class LockButton :public Button{
    public:
        LockButton(sf::RectangleShape* button);
        void update(sf::Vector2f mousePos);
        // getters
        bool getLock() const;

        // setters 
        void setLock(bool value);

    private:
        bool lock;
};