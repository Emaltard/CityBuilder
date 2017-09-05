#ifndef TILE_HPP
#define TILE_HPP

#include <string>

#include <SFML/Graphics.hpp>

#define TILE_WIDTH 64
#define TILE_HEIGHT 32

class Tile
{
	private:


	public:
    sf::Sprite sprite;
    sf::Text text;

    sf::Vector2i coordinates;

    void setPosition(int x, int y);

		Tile(sf::Sprite sprite, std::string text);
		~Tile();
};

#endif /* TILE_HPP */
