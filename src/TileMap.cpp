#include "TileMap.h"

TileMap::TileMap(sf::Vector2i map_size, sf::Vector2i tile_size, const std::string& tileset){
        this->map_size = map_size;
        this->nbr_tiles = this->map_size.x * this->map_size.y;
        this->tile_size = tile_size;

        m_tileset.loadFromFile(tileset);

        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(this->nbr_tiles * 4);

        level = (int *)malloc(sizeof(int)*this->nbr_tiles);

}

TileMap::~TileMap(){
        free(this->level);
}

sf::Vector2i TileMap::get_map_size() const {
        return this->map_size;
}
sf::Vector2i TileMap::get_tile_size() const {
        return this->tile_size;
}
int TileMap::get_tile_type(int tile_id) const {
        return this->level[tile_id];
}

bool TileMap::load(const std::string& map_file){

        std::ifstream file (map_file, std::ifstream::in);
        if(!file.is_open()) {
                std::cout << "Cannot open this file: " << map_file <<'\n';
                return false;
        }

        for(int i=0; i<this->nbr_tiles; i++) {
                file >> this->level[i];
        }

        for (auto i = 0; i < this->map_size.x; ++i)
                for (auto j = 0; j < this->map_size.y; ++j)
                {
                        int tileType = this->level[i + j * this->map_size.x];

                        // find its position in the tileset texture
                        int tu = tileType % (this->m_tileset.getSize().x / this->tile_size.x);
                        int tv = tileType / (this->m_tileset.getSize().x / this->tile_size.x);

                        // get a pointer to the current tile's quad
                        sf::Vertex* quad = &m_vertices[(i + j * this->map_size.x) * 4];

                        int pos_x = this->tile_size.x/2*i - this->tile_size.x/2*j;
                        int pos_y = this->tile_size.y/2*i + this->tile_size.y/2*j;

                        // define its 4 corners
                        quad[0].position = sf::Vector2f(pos_x, pos_y);
                        quad[1].position = sf::Vector2f(pos_x + this->tile_size.x, pos_y);
                        quad[2].position = sf::Vector2f(pos_x + this->tile_size.x, pos_y + this->tile_size.y);
                        quad[3].position = sf::Vector2f(pos_x, pos_y + this->tile_size.y);


                        // define its 4 texture coordinates
                        quad[0].texCoords = sf::Vector2f(tu * this->tile_size.x, tv * this->tile_size.y);
                        quad[1].texCoords = sf::Vector2f((tu + 1) * this->tile_size.x, tv * this->tile_size.y);
                        quad[2].texCoords = sf::Vector2f((tu + 1) * this->tile_size.x, (tv + 1) * this->tile_size.y);
                        quad[3].texCoords = sf::Vector2f(tu * this->tile_size.x, (tv + 1) * this->tile_size.y);
                }

        return true;
}

bool TileMap::update(int tileNumber, int type_id){

        this->level[tileNumber] = type_id;
        int tu = type_id % (m_tileset.getSize().x / this->tile_size.x);
        int tv = 0 / (m_tileset.getSize().x / this->tile_size.x);

        // get a pointer to the current tile's quad
        sf::Vertex* quad = &m_vertices[tileNumber * 4];

        quad[0].texCoords = sf::Vector2f(tu * this->tile_size.x, tv * this->tile_size.y);
        quad[1].texCoords = sf::Vector2f((tu + 1) * this->tile_size.x, tv * this->tile_size.y);
        quad[2].texCoords = sf::Vector2f((tu + 1) * this->tile_size.x, (tv + 1) * this->tile_size.y);
        quad[3].texCoords = sf::Vector2f(tu * this->tile_size.x, (tv + 1) * this->tile_size.y);
        // Change Vertex Color
        // quad[0].color = sf::Color(50, 50, 50, 255);
        // quad[1].color = sf::Color(50, 50, 50, 255);
        // quad[2].color = sf::Color(50, 50, 50, 255);
        // quad[3].color = sf::Color(50, 50, 50, 255);
}

bool TileMap::save(const std::string& map_file){
        std::ofstream file(map_file);
        if(!file.is_open()) {
                std::cout << "Cannot open this file: " << map_file <<'\n';
                return false;
        }

        for(int i = 0; i<this->map_size.x; i++) {
                for(int j = 0; j<this->map_size.y; j++) {
                        int current_tile = i * this->map_size.x + j;
                        file << this->level[current_tile] << " ";
                }
                file << std::endl;
        }
        file.close();
        return true;
}
