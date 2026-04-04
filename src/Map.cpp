#include "Map.hpp"

Map::Map(float w, float h){
    width = w * 0.6;
    height = h * 0.3;
    xTiles = 12;
    yTiles = 6;
    tileWidth = width / xTiles;
    tileHeight = height / yTiles;
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

//Draw the map
void Map::draw(sf::RenderWindow& window){
    for(int i = 0; i < xTiles; i++){
        for(int j = 0; j < yTiles; j++){
            sf::RectangleShape tile(sf::Vector2f(tileWidth, tileHeight));
            tile.setPosition({i * tileWidth + (width * 0.4)/0.6, j * tileHeight + (height *0.35)/0.3});
            tile.setFillColor(sf::Color(100, 100, 100));
            tile.setOutlineThickness(1);
            tile.setOutlineColor(sf::Color(50, 50, 50));
            window.draw(tile);
        }
    }
}