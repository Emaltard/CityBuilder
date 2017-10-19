#include "iostream"

#include "map.hpp"

Map::Map(int size){
        this->size = size;
        this->offset.x = 400-32;
        this->offset.y = 0;

        this->texture_grass.loadFromFile("Media/grass.iso.png");
        this->texture_grass.setSmooth(true);
        this->texture_normal.loadFromFile("Media/normal.iso.png");
        this->texture_normal.setSmooth(true);
        this->font.loadFromFile("Media/font.ttf");

        for(int i = 0; i<this->size; i++) {
                for(int j = 0; j<this->size; j++) {
                        int current_tile = i * this->size + j;
                        this->map.push_back(new Tile(this->sprite, std::to_string(current_tile)));
                        if(i<9)
                                this->map[current_tile]->sprite.setTexture(this->texture_grass);
                        else
                                this->map[current_tile]->sprite.setTexture(this->texture_normal);
                        this->map[current_tile]->setPosition(TILE_WIDTH/2*j - TILE_WIDTH/2*i + this->offset.x, TILE_HEIGHT/2*j + TILE_HEIGHT/2*i + this->offset.y);
                        this->map[current_tile]->text.setFont(this->font);
                }
        }

}

Map::~Map()
{
        for(int i = 0; i < this->size * this->size; i++) {
                delete this->map[i];
        }
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        for(int i = 0; i < this->size * this->size; i++) {
                //OPTI A FAIRE
                if(this->map[i]->sprite.getPosition().y<target.getSize().y && this->map[i]->sprite.getPosition().x<target.getSize().x && this->map[i]->sprite.getPosition().x>-TILE_WIDTH && this->map[i]->sprite.getPosition().y>-TILE_HEIGHT) {
                        target.draw(this->map[i]->sprite, states);
                        //target.draw(this->map[i]->text, states);
                }
        }
}

void Map::select_tile(sf::Vector2i coord_map){
        if(coord_map.x<this->size && coord_map.y<this->size && coord_map.x>=0 && coord_map.y>=0) {
                int current_tile = int(coord_map.y) * this->size + int(coord_map.x);
                this->tiles_selected.push_back(this->map[current_tile]);
                this->tiles_selected.back()->sprite.setColor(sf::Color(0, 0, 255));
        }
}

sf::Vector2i Map::screen_to_map(sf::Vector2i screen_pixels){
        int screen_x = screen_pixels.x - TILE_WIDTH/2;
        int screen_y = screen_pixels.y;
        screen_x -= offset.x;
        screen_y -= offset.y;
        float x = (float(screen_x) / float(TILE_WIDTH/2) + float(screen_y) / float(TILE_HEIGHT/2)) /2.0;
        float y = (float(screen_y) / float(TILE_HEIGHT/2) -(float(screen_x) / float(TILE_WIDTH/2))) /2.0;
        return sf::Vector2i(int(x),int(y));
}
