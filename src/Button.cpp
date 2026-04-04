#include "Button.hpp"

#include <cstdint>

Button::Button(sf::RectangleShape* button)
    : button(button), mousePressed(false), pressedInside(false), toggle(false)
{}

void Button::update(sf::Vector2f mousePos) {
    bool isOver = button->getGlobalBounds().contains(mousePos);
    bool justPressed  = false;
    bool justReleased = false;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if (!mousePressed) justPressed = true;
        mousePressed = true;
    } else {
        if (mousePressed) justReleased = true;
        mousePressed = false;
    }

    if (isOver && justPressed)
        pressedInside = true;

    if (justReleased && pressedInside && isOver) {
        if (canToggle())
            toggle = !toggle;
        _flashing = true;
        _flashClock.restart();
    }

    if (justReleased && pressedInside)
        pressedInside = false;

    // visual feedback — flash takes priority over everything
    if (_flashing) {
        float t = _flashClock.getElapsedTime().asSeconds();
        if (t < 0.25f) {
            // pulse white then fade back
            float pulse = 1.f - (t / 0.25f);
            int r = (int)(255);
            int g = (int)(255 * pulse + 170 * (1.f - pulse));
            int b = (int)(255 * pulse);
            button->setFillColor(sf::Color(r, g, b));
            return; // skip normal color logic while flashing
        } else {
            _flashing = false;
        }
    }

    // normal hover colors
    if (isOver)
        button->setFillColor(sf::Color(0, 170, 255));
    else
        button->setFillColor(sf::Color::White);
}

bool Button::getToggle() const {
    return toggle;
}

void Button::setToggle(bool value) {
    toggle = value;
}

bool Button::canToggle() const {
    return true;
}