#include "tile.hpp"
#include "iostream"

Tile::Tile(sf::Sprite sprite, std::string text){
  this->sprite = sprite;
  this->text.setString(text);
  this->text.setFillColor(sf::Color::Red);
  this->text.setCharacterSize(15);
}

Tile::~Tile()
{

}

void Tile::setPosition(int x, int y){
  this->sprite.setPosition( x, y);
  this->text.setPosition( x + 25, y + 55);
}