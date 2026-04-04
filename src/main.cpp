#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

sf::Font font;
if(!font.openFromFile("ttf/Hack-Regular.ttf")){
    std::cerr << "Failed to load font\n";
    return -1;
}
sf::Text text(font);
text.setString("Hellow");
text.setCharacterSize(24); // in pixels, not points
text.setFillColor(sf::Color::Red);

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
        window.draw(text);
        window.display();

    }
}