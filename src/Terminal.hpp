#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window.hpp>

#include "Creature.hpp"
#include "Rune.hpp"

#include <string>
#include <vector>

class Terminal {
    public:
        Terminal();
        void update(std::string);
        void drawTerminal(sf::RenderWindow&);

        void setupTerminal(Creature creature);

        

    private:
        std::vector<sf::Text> _textArr;
        std::vector<sf::Drawable> _terminalPieces;
        int _bigPrime = 178697;
        

};