#include "LockButton.hpp"
#include "Button.hpp"

LockButton::LockButton(sf::RectangleShape* button)
    : Button(button),
      lock(false)
{}

void LockButton::update(sf::Vector2f mousePos){
    Button::update(mousePos);
    // toggle logic (now internal)
    if (getToggle()){
        lock = true;
    }
}

// getters
bool LockButton::getLock() const{
    return lock;
}

// setters
void LockButton::setLock(bool value){
    lock = value;
}
