#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>

#include "tile.hpp"

class Map : public sf::Drawable
{
private:

sf::Sprite sprite;
sf::Font font;
public:
int size;
sf::Vector2i offset;

Map(int size);
~Map();
std::vector<Tile*> map;
std::vector<Tile*> tiles_selected;
std::vector<sf::Texture> texture_vector;
sf::Vector2i screen_to_map(sf::Vector2i screen_pixels);

void select_tile(sf::Vector2i coord);

virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif /* MAP_HPP */
