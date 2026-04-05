#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <optional>

class Map{
public:
    Map(float, float);
    void draw(sf::RenderWindow& window);
    float getWidth();
    float getTileWidth();
    float getHeight();
    float getTileHeight();
    int getXTiles();
    int getYTiles();
    void selectTile(int,int);
    int occupied[12][6];
    int selectedX;
    int selectedY;

    void clearOccupied();

    int getCastleHealth() const { return _castleHealth; }
    void damageCastle() { _castleHealth--; }
    bool castleDestroyed() const { return _castleHealth <= 0; }
    

    
    private:

    float width;
    float tileWidth;
    float height;
    float tileHeight;
    int xTiles;
    int yTiles;

    sf::Texture _lightTile;
    sf::Texture _darkTile;
    bool _tilesLoaded = false;

    sf::Texture              _castleTexture;
    std::optional<sf::Sprite> _castleSprite;

    int _castleHealth = 10;
};

#endif