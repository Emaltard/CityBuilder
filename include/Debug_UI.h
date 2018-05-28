#ifndef DEBUG_UI_H_
#define DEBUG_UI_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "Game.h"
#include "TileMap.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "imconfig-SFML.h"

void ImGui_UI(sf::RenderWindow &App, Game &game, TileMap &map, sf::View &view, ImGuiIO &io, float imgui_color[3], int &map_size, int screen_x, int screen_y, int x, int y);

#endif // DEBUG_UI_H_
