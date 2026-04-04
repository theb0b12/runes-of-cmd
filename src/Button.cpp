#include "Button.hpp"

Button::Button(sf::RectangleShape* button)
    : button(button),
      mousePressed(false),
      pressedInside(false),
      toggle(false)
{}

void Button::update(sf::Vector2f mousePos)
{
    bool isOver = button->getGlobalBounds().contains(mousePos);

    bool justPressed = false;
    bool justReleased = false;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
        if (!mousePressed)
            justPressed = true;

        mousePressed = true;
    }
    else{
        if (mousePressed)
            justReleased = true;

        mousePressed = false;
    }

    if (isOver && justPressed){
        pressedInside = true;
    }

    if (justReleased && pressedInside){
        pressedInside = false;
    }

    // toggle logic (now internal)
    if (justReleased && pressedInside && isOver){
        toggle = !toggle;
    }

    // visual feedback
    if (isOver)
        button->setFillColor(sf::Color(0, 170, 255));
    else
        button->setFillColor(sf::Color::White);
}

// getters
bool Button::getToggle() const{
    return toggle;
}




// setters
void Button::setToggle(bool value){
    toggle = value;
}
