#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Rune.hpp"
#include "rune-types/TwistRune.hpp"
#include "rune-types/SightRune.hpp"
#include "rune-types/ChoiceRune.hpp"
#include "rune-types/WindRune.hpp"
#include "rune-types/ViolenceRune.hpp"
#include "LockButton.hpp"
#include "Creature.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Terminal.hpp"
#include <iostream>

const int windX = 1920;
const int windY = 1080;

std::vector <Rune> transform(std::vector <int> vec, Creature* holder, Map& map){
    std::vector <Rune> output;
    for(int i = 0; i < vec.size(); i++ ){
        switch(vec[i]){
            case 1:
            output.push_back(Sight(holder,map));
            break;
            case 2:
            output.push_back(Choice(holder,map));
            break;
            case 3:
            output.push_back(Rune("Harmony",holder,map));
            break;
            case 4:
            output.push_back(Rune("Discord",holder,map));
            break;
            case 5:
            output.push_back(Wind(holder,map));
            break;
            case 6:
            output.push_back(Twist(holder,map));
            break;
            case 7:
            output.push_back(Violence(holder,map));
            break;
        }
    }
    return output;
}

int main(){
    sf::RenderWindow window(sf::VideoMode({windX, windY}), "Runes of CMD",sf::Style::Default/*,sf::State::Fullscreen*/);
    sf::Vector2u windowSize = window.getSize();
    auto [windX, windY] = windowSize;
    float windowX = (float)windX;
    float windowY = (float)windY; 
    // frame rate set as not to have it hardware limited
    window.setFramerateLimit(60);

    // clock instantiation
    sf::Clock clock;

    Player player;
    player.setSpeed(300);

    Map map(windowX, windowY);

    
    //Creature Feature featuring the creature
    Creature C1(3,4,-2,true,0);

    // Terminal terminal;
    // terminal.setupTerminal(C1);
    
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
        float dt = clock.restart().asSeconds();

        // player controls
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
            player.moveBy(0,1, dt);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
            player.moveBy(0,-1, dt);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
            player.moveBy(1,0, dt);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            player.moveBy(-1,0, dt);
        }
        // mouse position
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f mouse_position = window.mapPixelToCoords(pixelPos);

        guiButton.update(mouse_position);

        // displaying stuff
        window.clear();
        map.draw(window);
        C1.drawCreature(window,map);
        player.printPlayer(window);
        if (guiButton.getToggle()) {
            //terminal.drawTerminal(window);
        }
        else {
            window.draw(myButton);
        }

        window.display();

    }
}