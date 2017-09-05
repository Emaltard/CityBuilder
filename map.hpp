#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>

#include "tile.hpp"

#define SIZE 10

class Map : public sf::Drawable
{
  private :
    sf::Texture texture_grass;
    sf::Sprite sprite;
    sf::Font font;
    std::vector<Tile> map;
  public :

    Map();
    ~Map();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif /* MAP_HPP */
