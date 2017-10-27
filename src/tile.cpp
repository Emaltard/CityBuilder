#include "tile.hpp"
#include "iostream"

Tile::Tile(sf::Sprite sprite, std::string text){
        this->sprite = sprite;
        this->text.setString(text);
        this->text.setFillColor(sf::Color::Red);
        this->text.setCharacterSize(15);
        this->type_id = 0;
}

Tile::~Tile()
{

}

void Tile::setPosition(int x, int y){
        this->sprite.setPosition( x, y);
        this->text.setPosition( x + TILE_WIDTH/2 - 10, y + TILE_HEIGHT/2 - 10);
}
