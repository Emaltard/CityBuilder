#ifndef TILEMAP_H_
#define TILEMAP_H_

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
      private:
        int *level;

        sf::VertexArray m_vertices;
        sf::Texture m_tileset;

        sf::Vector2i map_size;
        unsigned int nbr_tiles;
        sf::Vector2i tile_size;

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
        {
                // apply the transform
                states.transform *= getTransform();

                // apply the tileset texture
                states.texture = &m_tileset;

                // draw the vertex array
                target.draw(m_vertices, states);
        }

      public:
        std::vector<int> tiles_selected;
        TileMap(sf::Vector2i tile_size, const std::string &tileset, const std::string &map_file);
        TileMap(sf::Vector2i map_size, sf::Vector2i tile_size, const std::string &tileset);
        ~TileMap();

        sf::Vector2i get_map_size() const;
        sf::Vector2i get_tile_size() const;
        int get_tile_type(int tile_id) const;

        void change_map_size(sf::Vector2i map_size);

        bool load(const std::string &map_file);
        bool update(int tileNumber, int type_id);
        bool save(const std::string &map_file);

        void set_tile_color_as_selected(int tile_id);
        void clear_tiles_selected();
        void select_tile(int tile_id);
        void select_line_tile(int start_tile, int end_tile);
        void select_rectangle_tile(int start_tile, int end_tile);
};

#endif // TILEMAP_H_
