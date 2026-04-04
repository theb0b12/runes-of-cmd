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
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 6; j++){
            sf::RectangleShape tile(sf::Vector2f(tileWidth, tileHeight));
            tile.setPosition({i * tileWidth + (width * 0.3f)/0.7f, (j - 3) * tileHeight + height/2});
            if((i+j) % 2 == 0){
               
                tile.setFillColor(sf::Color(25, 100, 25));  
            }else{
               
                tile.setFillColor(sf::Color(50, 175, 50));  
            }
            
            if(i == selectedX && j == selectedY ){
                tile.setFillColor(sf::Color::Yellow);
            }
            tile.setOutlineThickness(2);
            tile.setOutlineColor(sf::Color(50, 50, 50));
            window.draw(tile);
        }
    }

    sf:: RectangleShape castle(sf::Vector2f{(width/0.7f) * 0.3f, height});
    castle.setFillColor(sf::Color(100,100,100));
    castle.setOutlineColor(sf::Color(50,50,50));
    window.draw(castle);
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