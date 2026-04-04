#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

sf::Font font("ttf/Hack-Regular.ttf");

int main(){
    sf::RenderWindow window(sf::VideoMode({720, 1280}), "Runes of CMD");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while(window.isOpen()){
        while(const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(); 
        window.draw(shape);
        window.display();

    }
}