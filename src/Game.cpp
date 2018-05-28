#include "Game.h"

void Game::init_bgColor(float r, float g, float b)
{
    this->bgColor.r = static_cast<sf::Uint8>(r);
    this->bgColor.g = static_cast<sf::Uint8>(g);
    this->bgColor.b = static_cast<sf::Uint8>(b);
}

void Game::change_bgColor(float r, float g, float b)
{
    this->bgColor.r = static_cast<sf::Uint8>(r * 255.f);
    this->bgColor.g = static_cast<sf::Uint8>(g * 255.f);
    this->bgColor.b = static_cast<sf::Uint8>(b * 255.f);
}
