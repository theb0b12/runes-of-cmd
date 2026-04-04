#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

void processButton(sf::RectangleShape *guiButton, sf::Vector2f mouse_position){
    // state of button
    bool isOver = false;
    bool isPressedInside = false;

    // state of mouse
    bool isMousePressed = false;
    bool onMousePress   = false;
    bool onMouseRelease = false;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
        if (!isMousePressed)
            onMousePress = true;
        isMousePressed = true;
    }
    else{
        if (isMousePressed)
            onMouseRelease = true;
        isMousePressed = false;
    }

    // when mouse is over button
    if (guiButton->getGlobalBounds().contains(mouse_position)){
        // on mouse press
        if (onMousePress){
            std::cout << "Press\n";
            // set pressed inside
            isPressedInside = true;
        }

        // on mouse release
        if (onMouseRelease and isPressedInside)
            std::cout << "Release\n";

        // when mouse is pressed
        if (isMousePressed and isPressedInside)
            guiButton->setFillColor(sf::Color::Yellow);
        else
            guiButton->setFillColor(sf::Color(0, 170, 255));

        // set state
        isOver = true;
    }
    else{
        guiButton->setFillColor(sf::Color::White);

        // on mouse leave
        if (isOver)
            std::cout << "Leave\n";

        // reset state
        isOver = false;
    }

    // reset pressed inside
    if (not isMousePressed)
        isPressedInside = false;
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
        sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition(window));

        processButton(&guiButton, mouse_position);

        window.clear(); 
        window.draw(guiButton);
        window.draw(text);
        window.display();

    }
}