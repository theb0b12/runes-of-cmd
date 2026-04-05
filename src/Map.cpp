#include "Map.hpp"
#include <iostream>

Map::Map(float w, float h){
    width = w * 0.7;
    height = h;
    xTiles = 12;
    yTiles = 6;
    tileWidth = width / xTiles;
    tileHeight = tileWidth;
    occupied[12][6] = {0};
    selectedX = 5;
    selectedY = 3;

    if (!_lightTile.loadFromFile("assets/grass_tile/light.png"))
        std::cerr << "Failed to load light tile\n";
    if (!_darkTile.loadFromFile("assets/grass_tile/dark.png"))
        std::cerr << "Failed to load dark tile\n";
    _tilesLoaded = true;

    if (!_castleTexture.loadFromFile("assets/castle/castle.png"))
        std::cerr << "Failed to load castle texture\n";
    _castleSprite = sf::Sprite(_castleTexture);
    float castleW = (width / 0.7f) * 0.3f;
    _castleSprite->setScale({ castleW / _castleTexture.getSize().x,
                            height  / _castleTexture.getSize().y });
    _castleSprite->setPosition({ 0.f, 0.f });

}

// Getters
float Map::getWidth(){
    return width;
}
float Map::getTileWidth(){
    return tileWidth;
}
float Map::getHeight(){
    return height;
}
float Map::getTileHeight(){
    return tileHeight;
}
int Map::getXTiles(){
    return xTiles;
}
int Map::getYTiles(){
    return yTiles;
}

// Draw the map
void Map::draw(sf::RenderWindow& window){
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 6; j++){
            sf::RectangleShape tile(sf::Vector2f(tileWidth, tileHeight));
            tile.setPosition({i * tileWidth + (width * 0.3f)/0.7f, (j - 3) * tileHeight + height/2});
            
            if(_tilesLoaded) {
                tile.setTexture((i+j) % 2 == 0 ? &_lightTile : &_darkTile);
            } else {
                tile.setFillColor((i+j) % 2 == 0 ? sf::Color(25,100,25) : sf::Color(50,175,50));
            }

            tile.setOutlineThickness(2);
            tile.setOutlineColor(sf::Color(50, 50, 50));
            window.draw(tile);
        }
    }

    if (_castleSprite) window.draw(*_castleSprite);

    sf::RectangleShape stands(sf::Vector2{width, (height - (tileHeight * 6))/6});
    for(int i = 0 ; i < 3; i++){
        stands.setFillColor(sf::Color(150/(i+1),75/(i+1),0));
        stands.setPosition({(width/0.7f)*0.3f,((height - (tileHeight * 6))/6) * i});
        window.draw(stands);

        stands.setPosition({(width/0.7f)*0.3f,(height - ((height - (tileHeight * 6))/6) * (i+1))});
        window.draw(stands);
    }
}

void Map::selectTile(int x, int y){
    selectedX = x;
    selectedY = y;
}

void Map::clearOccupied() {
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 6; j++)
            occupied[i][j] = 0;
}