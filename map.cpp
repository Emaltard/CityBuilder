#include "map.hpp"
#include "iostream"

Map::Map(){

  int offset_x = 0;
  int offset_y = 35-80;

  this->texture_grass.loadFromFile("Media/grass.iso.png");
  this->font.loadFromFile("Media/font.ttf");

  for(int i = 0; i<SIZE; i++){
    for(int j = 0; j<SIZE; j++){
      int current_tile = i * SIZE + j;
      this->map.push_back(Tile(this->sprite, std::to_string(i * SIZE+j)));
      this->map[current_tile].sprite.setTexture(this->texture_grass);
      this->map[current_tile].setPosition(TILE_WIDTH/2*j - TILE_WIDTH/2*i + offset_x, TILE_HEIGHT/2*j + TILE_HEIGHT/2*i + offset_y);
      this->map[current_tile].text.setFont(this->font);
    }
  }
}

Map::~Map()
{

}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const{
  for(int i = 0; i < SIZE * SIZE; i++){
    //OPTI A FAIRE
    if(this->map[i].sprite.getPosition().y<target.getSize().y){
      target.draw(this->map[i].sprite, states);
      target.draw(this->map[i].text, states);
    }
  }
}
