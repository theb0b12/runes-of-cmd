#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "LockButton.hpp"
#include "Map.hpp"
#include <iostream>

const int windX = 1920;
const int windY = 1080;



int main(){
    sf::RenderWindow window(sf::VideoMode({windX, windY}), "Runes of CMD",sf::Style::Default/*,sf::State::Fullscreen*/);
    sf::Vector2u windowSize = window.getSize();
    auto [windX, windY] = windowSize;
    float windowX = (float)windX;
    float windowY = (float)windY; 

    Map map(windowX, windowY);

    sf::Font font;
    if(!font.openFromFile("ttf/Hack-Regular.ttf")){
        std::cerr << "Failed to load font\n";
        return -1;
    }

    sf::Text text(font);
    text.setString("Hellow");
    text.setCharacterSize(24); // in pixels, not points
    text.setFillColor(sf::Color::Red);


    // create the terminal thing
    sf::RectangleShape terminal({windowX * 0.7f,windowY * 0.7f});
    terminal.setOrigin(terminal.getGeometricCenter());
    terminal.setPosition({windowX/2, windowY/2});
    
    // create the terminal open button
    sf::RectangleShape myButton({200.f, 100.f});
    myButton.setOrigin(myButton.getGeometricCenter());
    myButton.setPosition({400.f, 300.f});

    LockButton guiButton(&myButton);
    
    while(window.isOpen()){
        while(const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>())
                window.close();
        }
        // mouse position
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f mouse_position = window.mapPixelToCoords(pixelPos);

        guiButton.update(mouse_position);

        // displaying stuff
        window.clear();
        map.draw(window);
        if (guiButton.getToggle()) {
            window.draw(terminal);
        }
        else {
            window.draw(myButton);
        }

        window.display();

    }
}