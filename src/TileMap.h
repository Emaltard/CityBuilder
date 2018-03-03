#ifndef TILEMAP_H_
#define TILEMAP_H_

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
private:

sf::VertexArray m_vertices;
sf::Texture m_tileset;

sf::Vector2i map_size;
unsigned int nbr_tiles;
sf::Vector2i tile_size;

virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
}

public:

int* level;

TileMap(sf::Vector2i map_size, sf::Vector2i tile_size, const std::string& tileset);
~TileMap();

sf::Vector2i get_map_size() const;
sf::Vector2i get_tile_size() const;
int get_tile_type(int tile_id) const;

bool load(const std::string& map_file);
bool update(int tileNumber, int type_id);
bool save(const std::string& map_file);

};

#endif  // TILEMAP_H_
