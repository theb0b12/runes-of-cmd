#include "Button.hpp"

#include <cstdint>

Button::Button(sf::RectangleShape* button)
    : button(button), mousePressed(false), pressedInside(false), toggle(false)
{
    _originalColor = button->getFillColor();
}

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

    // visual feedback — flash takes full priority, then hover, then original
    if (_flashing) {
        float t = _flashClock.getElapsedTime().asSeconds();
        if (t < 0.25f) {
            float pulse = 1.f - (t / 0.25f);
            button->setFillColor(sf::Color(
                (int)(_originalColor.r + (255 - _originalColor.r) * pulse),
                (int)(_originalColor.g + (255 - _originalColor.g) * pulse),
                (int)(_originalColor.b + (255 - _originalColor.b) * pulse)
            ));
        } else {
            _flashing = false;
            button->setFillColor(_originalColor);
        }
        return; // skip everything else while flashing
    }

    if (isOver)
        button->setFillColor(sf::Color(
            (int)(_originalColor.r * 0.6f),
            (int)(_originalColor.g * 0.6f + 170 * 0.4f),
            (int)(_originalColor.b * 0.6f + 255 * 0.4f)
        ));
    else
        button->setFillColor(_originalColor);
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