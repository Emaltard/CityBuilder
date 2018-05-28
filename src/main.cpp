#include <iostream>
#include <fstream>
#include "imgui.h"
#include "imgui-SFML.h"
#include "imconfig-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include "Game.h"
#include "Event.h"
#include "Debug_UI.h"

int main()
{
        sf::RenderWindow App(sf::VideoMode(1280, 720, 32), "City Builder");
        App.setFramerateLimit(60);

        ImGui::CreateContext();
        ImGui::SFML::Init(App);
        ImGuiIO &io = ImGui::GetIO();

        TileMap map(sf::Vector2i(64, 32), "Media/tileset.png", "saves/map.txt");
        //TileMap map(sf::Vector2i(10,10), sf::Vector2i(64,32), "Media/tileset.png");

        int map_size = map.get_map_size().x;

        sf::View view(sf::FloatRect(0, 0, 1280, 720));
        view.setCenter(32, map.get_tile_size().y * (map.get_map_size().x / 2));
        App.setView(view);

        Game game;

        float imgui_color[3] = {60.f / 255.f, 60.f / 255.f, 60.f / 255.f};
        game.init_bgColor(imgui_color[0] * 255.f, imgui_color[1] * 255.f, imgui_color[2] * 255.f);

        while (App.isOpen())
        {
                // récupération de la position de la souris dans la fenêtre
                sf::Vector2i pixelPos = sf::Mouse::getPosition(App);

                // conversion en coordonnées "monde"
                sf::Vector2i position = (sf::Vector2i)App.mapPixelToCoords(pixelPos);

                int screen_x = position.x - 64 / 2;
                int screen_y = position.y;

                float y = (float(screen_x) / float(64 / 2) + float(screen_y) / float(32 / 2)) / 2.0;
                float x = (float(screen_y) / float(32 / 2) - (float(screen_x) / float(64 / 2))) / 2.0;
                if ((x >= map.get_map_size().x) || (y >= map.get_map_size().y) || (x < 0) || (y < 0))
                {
                        game.current_tile = -1;
                }
                else
                {
                        game.current_tile = (int)x * map.get_map_size().x + (int)y;
                }

                if (game.selection_state && (game.current_tile != -1))
                {
                        map.clear_tiles_selected();
                        if (game.selection_mode == 0)
                        {
                                map.select_line_tile(game.first_tile_selected, game.current_tile);
                        }
                        else if (game.selection_mode == 1)
                        {
                                map.select_rectangle_tile(game.first_tile_selected, game.current_tile);
                        }
                }

                handle_Events(App, game, map, view, io);

                ImGui_UI(App, game, map, view, io, imgui_color, map_size, screen_x, screen_y, x, y);

                App.clear(game.bgColor);
                App.draw(map);
                ImGui::SFML::Render(App);

                App.display();
        }
        map.save("saves/map.txt");
        ImGui::SFML::Shutdown();
}
