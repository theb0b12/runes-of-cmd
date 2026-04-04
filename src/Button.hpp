#pragma once

#include <SFML/Graphics.hpp>

class Button
{
public:
    explicit Button(sf::RectangleShape* button);
    void update(sf::Vector2f mousePos);

    // getters
    bool getToggle() const;
    bool getLock() const;

    // setters 
    void setToggle(bool value);
    void setLock(bool value);

private:
    sf::RectangleShape* button;
    bool mousePressed;
    bool pressedInside;

    bool toggle;
    bool lock;
};