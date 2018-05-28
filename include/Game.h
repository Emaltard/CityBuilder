#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.hpp>
#include "TileMap.h"

class Game
{
  private:
  public:
    void init_bgColor(float r, float g, float b);
    void change_bgColor(float r, float g, float b);

    bool ctrl_hold = false;
    int type_id = 0;
    sf::Color bgColor;

    sf::Clock deltaClock;
    char windowTitle[255] = "City Builder";
    int current_tile = -1;
    bool selection_state = false;
    int selection_mode = 1;
    int first_tile_selected;
};

#endif // GAME_H_
