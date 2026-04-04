#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window.hpp>

#include "Creature.hpp"
#include "Map.hpp"
#include "Rune.hpp"

#include <string>
#include <vector>

class Terminal {
    public:
        Terminal(std::vector <Rune> runeArr, Creature*, Map&);
        void update(std::string);
        void drawTerminal(sf::RenderWindow&);

        void setupTerminal(Creature creature);

        

    private:
        std::vector<sf::Text> _textArr;
        std::vector<sf::Drawable> _terminalPieces;
        std::vector <Rune> runeArr;
        Creature* creature;
        static Map& map;

        int _bigPrime = 178697;
        

};