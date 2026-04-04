#include "Terminal.hpp"
#include "Creature.hpp"
#include "Map.hpp"
 

#include <iostream>
#include <string>


// constructor
Terminal::Terminal(std::vector <Rune> runeArr, Creature* creature, Map& m){
    map = m;
    this->runeArr = runeArr;
    this->creature = creature;
    
}


void Terminal::update(std::string text){

}

void Terminal::setupTerminal(Creature creature){
   
    sf::Font font;
    if(!font.openFromFile("ttf/Hack-Regular.ttf")){
        std::cerr << "Failed to load font\n";
    }
    // outer terminal box
    sf::RectangleShape terminalBBox({1920 * 0.8f, 1080 * 0.8f});
    terminalBBox.setFillColor(sf::Color{ 65, 65, 65, 1 }); // gray ish
    terminalBBox.setOrigin(terminalBBox.getGeometricCenter());
    terminalBBox.setPosition({1920.f/2, 1080.f/2});

    _terminalPieces.push_back(terminalBBox);

    // box around text and "code editor"
    sf::RectangleShape terminalSBox({1920 * 0.8f, 1080 * 0.4f});
    terminalSBox.setFillColor(sf::Color{ 79, 79, 79, 1 }); // gray ish
    terminalSBox.setOrigin(terminalSBox.getGeometricCenter());
    terminalSBox.setPosition({1920.f/2, 1080.f/4});

    _terminalPieces.push_back(terminalSBox);

    // terminal title text thing
    sf::Text title(font);

    std::string id = "[" + std::to_string(creature.getId() * _bigPrime) + "~]$ ";
    title.setString(id);
    title.setCharacterSize(15);

    title.setFillColor(sf::Color{ 128, 128, 128, 1 }); // gray ish

    title.setPosition({400.f, 300.f});

    _terminalPieces.push_back(title);

    // rune display area
    


    // rune selection area


}

void Terminal::drawTerminal(sf::RenderWindow& window){
    for(int i = 0; i < _terminalPieces.size(); i++){
        window.draw(_terminalPieces[i]);
    }
}