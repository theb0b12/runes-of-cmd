#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

void processButton(sf::RectangleShape *button, sf::Vector2f mousePos)
{
    static bool mousePressed = false;
    static bool pressedInside = false;

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
        // std::cout << "Press\n";
    }

    if (justReleased && pressedInside){
        // std::cout << "Release\n";
        pressedInside = false;
    }

    if (isOver && mousePressed)
        button->setFillColor(sf::Color::Yellow);
    else if (isOver)
        button->setFillColor(sf::Color(0, 170, 255));
    else
        button->setFillColor(sf::Color::White);
}

int main(){
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Runes of CMD");


    sf::Font font;
    if(!font.openFromFile("ttf/Hack-Regular.ttf")){
        std::cerr << "Failed to load font\n";
        return -1;
    }

    sf::Text text(font);
    text.setString("Hellow");
    text.setCharacterSize(24); // in pixels, not points
    text.setFillColor(sf::Color::Red);


    // create the shape of button
    sf::RectangleShape guiButton({200.f, 100.f});
    guiButton.setOrigin(guiButton.getGeometricCenter());
    guiButton.setPosition({400.f, 300.f});

    

    
    while(window.isOpen()){
        while(const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>())
                window.close();
        }
        // mouse position
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f mouse_position = window.mapPixelToCoords(pixelPos);

        processButton(&guiButton, mouse_position);

        window.clear(); 
        window.draw(guiButton);
        // window.draw(text);
        window.display();

    }
}