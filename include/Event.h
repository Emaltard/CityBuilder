#ifndef EVENT_H_
#define EVENT_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "Game.h"
#include "TileMap.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "imconfig-SFML.h"

void handle_Events(sf::RenderWindow &App, Game &game, TileMap &map, sf::View &view, ImGuiIO &io);

#endif // EVENT_H_
