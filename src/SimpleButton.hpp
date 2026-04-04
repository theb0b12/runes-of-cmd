#pragma once
#include "Button.hpp"

class SimpleButton : public Button {
public:
    SimpleButton(sf::RectangleShape* shape) : Button(shape) {}
    void update(sf::Vector2f mousePos) override { Button::update(mousePos); }
protected:
    bool canToggle() const override { return true; }
};