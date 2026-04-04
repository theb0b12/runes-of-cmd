#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

class Button {
public:
    Button(sf::RectangleShape* button);
    virtual void update(sf::Vector2f mousePos);
    bool getToggle() const;
    void setToggle(bool value);

protected:
    sf::RectangleShape* button;
    bool mousePressed;
    bool pressedInside;
    bool toggle;
    virtual bool canToggle() const;

private:
    sf::Clock _flashClock;
    bool      _flashing = false;
};