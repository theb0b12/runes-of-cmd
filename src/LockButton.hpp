#pragma once
#include "Button.hpp"
#include <SFML/Graphics.hpp>

class LockButton :public Button{
    public:
        LockButton(sf::RectangleShape* button);
        void update(sf::Vector2f mousePos) override;
        // getters
        bool getLock() const;

        // setters 
        void setLock(bool value);
    protected:
        // override toggle permission
        bool canToggle() const override;

    private:
        bool lock;

};