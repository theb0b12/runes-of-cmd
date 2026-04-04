#include "Terminal.hpp"


#include <iostream>
#include <string>

using namespace std;
// constructor
Terminal::Terminal(){
    sf::RectangleShape terminal;

    
}


void Terminal::update(std::string text){

}

void Terminal::setupTerminal(Creature creature){
   
    sf::Font font;
    if(!font.openFromFile("ttf/Hack-Regular.ttf")){
        std::cerr << "Failed to load font\n";
    }
    // outer terminal box
    // create the terminal thing
    sf::RectangleShape terminalBBox({1920 * 0.8f, 1080 * 0.8f});
    terminalBBox.setFillColor(sf::Color{ 65, 65, 65, 1 }); // gray ish
    terminalBBox.setOrigin(terminalBBox.getGeometricCenter());
    terminalBBox.setPosition({1920.f/2, 1080.f/2});

    // box around text and "code editor"

    // terminal title text thing
    sf::Text title(font);

    string id = "[" + to_string(creature.getId() * _bigPrime) + "~]$ ";
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