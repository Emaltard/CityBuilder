#include <iostream>
#include <fstream>
#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "TileMap.h"

int main()
{
        sf::RenderWindow App(sf::VideoMode(1280, 720, 32), "City Builder");
        App.setFramerateLimit(60);
        ImGui::CreateContext();
        ImGui::SFML::Init(App);

        bool ctrl_hold = false;
        int type_id = 0;

        sf::Color bgColor;
        float color[3] = {60.f / 255.f, 60.f / 255.f, 60.f / 255.f};

        bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
        bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
        bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);

        sf::Clock deltaClock;
        char windowTitle[255] = "City Builder";

        TileMap map(sf::Vector2i(64, 32), "Media/tileset.png", "saves/map.txt");
        //TileMap map(sf::Vector2i(10,10), sf::Vector2i(64,32), "Media/tileset.png");

        int map_size = map.get_map_size().x;

        sf::View view(sf::FloatRect(0, 0, 1280, 720));
        view.setCenter(0, map.get_tile_size().y * (map.get_map_size().x / 2));
        App.setView(view);

        int current_tile = -1;
        bool selection_state = false;
        int selection_mode = 1;
        int first_tile_selected;

        sf::Clock clock; // démarre le chrono
        sf::Time elapsed1, elapsed2, elapsed3, elapsed4;
        elapsed1 = clock.getElapsedTime();
        elapsed2 = clock.getElapsedTime();
        elapsed3 = clock.getElapsedTime();
        elapsed4 = clock.getElapsedTime();
        float moy_render = 0;

        while (App.isOpen())
        {
                elapsed1 = clock.getElapsedTime();
                clock.restart();

                sf::Event Event;

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
                        current_tile = -1;
                }
                else
                {
                        current_tile = (int)x * map.get_map_size().x + (int)y;
                }

                while (App.pollEvent(Event))
                {
                        ImGui::SFML::ProcessEvent(Event);
                        switch (Event.type)
                        {
                        case sf::Event::Resized:
                        {
                                // on met à jour la vue, avec la nouvelle taille de la fenêtre
                                view.setSize(Event.size.width, Event.size.height);
                                App.setView(view);
                        }
                        break;
                        case sf::Event::Closed:
                                App.close();
                                break;
                        case sf::Event::KeyPressed:
                                if (Event.key.code == sf::Keyboard::Escape)
                                {
                                        App.close();
                                }
                                if (Event.key.code == sf::Keyboard::Left)
                                {
                                        view.move(-32, 0);
                                        App.setView(view);
                                }
                                if (Event.key.code == sf::Keyboard::Right)
                                {
                                        view.move(32, 0);
                                        App.setView(view);
                                }
                                if (Event.key.code == sf::Keyboard::Up)
                                {
                                        view.move(0, -32);
                                        App.setView(view);
                                }
                                if (Event.key.code == sf::Keyboard::Down)
                                {
                                        view.move(0, 32);
                                        App.setView(view);
                                }
                                break;
                        case sf::Event::KeyReleased:
                                if (Event.key.code == sf::Keyboard::LControl)
                                {
                                }
                                break;
                        case sf::Event::MouseButtonPressed:
                                if (Event.mouseButton.button == sf::Mouse::Left)
                                {
                                        if (current_tile > -1)
                                        {
                                                selection_state = true;
                                                first_tile_selected = current_tile;
                                        }
                                }
                                if (Event.mouseButton.button == sf::Mouse::Right)
                                {
                                }
                                break;
                        case sf::Event::MouseButtonReleased:
                                if (Event.mouseButton.button == sf::Mouse::Left)
                                {
                                        selection_state = false;
                                        for (auto it = map.tiles_selected.begin(); it != map.tiles_selected.end(); ++it)
                                        {
                                                map.update(*it, type_id);
                                        }
                                        map.clear_tiles_selected();
                                }
                                break;
                        default:
                                break;
                        }
                }

                if (selection_state && (current_tile != -1))
                {
                        map.clear_tiles_selected();
                        if (selection_mode == 0)
                        {
                                map.select_line_tile(first_tile_selected, current_tile);
                        }
                        else if (selection_mode == 1)
                        {
                                map.select_rectangle_tile(first_tile_selected, current_tile);
                        }
                }

                ImGui::SFML::Update(App, deltaClock.restart());

                ImGui::Begin("Sample window"); // begin window

                // Background color edit
                if (ImGui::ColorEdit3("Background color", color))
                {
                        // this code gets called if color value changes, so
                        // the background color is upgraded automatically!
                        bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
                        bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
                        bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
                }

                // Window title text edit
                if (ImGui::InputText("Window title", windowTitle, 255))
                {
                        App.setTitle(windowTitle);
                }

                if (ImGui::Button("Reset View Position"))
                {
                        view = App.getDefaultView();
                        view.setCenter(0, map.get_tile_size().y * (map.get_map_size().x / 2));
                        App.setView(view);
                }

                if (ImGui::InputInt("Map Size", &map_size))
                {
                }
                if (ImGui::Button("Set Map Size"))
                {
                        map.change_map_size(sf::Vector2i(map_size, map_size));
                }

                ImGui::Text("Map_size (width,height): %d, %d", map.get_map_size().x, map.get_map_size().y);

                if (ImGui::TreeNode("Tile Brush Selection"))
                {
                        static int selected = selection_mode;
                        if (ImGui::Selectable("Line", selected == 0, 0))
                        {
                                selected = 0;
                                selection_mode = 0;
                        }
                        if (ImGui::Selectable("Rectangle", selected == 1, 0))
                        {
                                selected = 1;
                                selection_mode = 1;
                        }
                        ImGui::TreePop();
                }

                if (ImGui::TreeNode("Tile Type Selection"))
                {
                        static int selected = 0;
                        for (int n = 0; n < 4; n++)
                        {
                                char buf[32];
                                sprintf(buf, "Type %d", n);

                                if (ImGui::Selectable(buf, selected == n, 0))
                                {
                                        selected = n;
                                        type_id = n;
                                }
                        }
                        ImGui::TreePop();
                }

                if (ImGui::IsMousePosValid())
                {
                        ImGui::Text("Mouse pos: (%d, %d)", screen_x, screen_y);
                }
                else
                        ImGui::Text("Mouse pos: <INVALID>");

                ImGui::Text("Tile (x,y): (%d, %d)", (int)x, (int)y);

                ImGui::Text("Tile Index: %d", current_tile);

                if (current_tile > -1)
                {
                        ImGui::Text("Tile Type: %d", map.get_tile_type(current_tile));
                }
                else
                {
                        ImGui::Text("Tile Type: None");
                }

                ImGui::ProgressBar(0.1);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

                ImGui::DrawRectFilled(sf::FloatRect(0, 0, elapsed1.asMilliseconds() * 50, 15), sf::Color(60, 60, 255));
                ImGui::NewLine();
                ImGui::DrawRectFilled(sf::FloatRect(0, 0, (elapsed3.asMilliseconds() - elapsed2.asMilliseconds()) * 50, 15), sf::Color(255, 60, 60));
                ImGui::DrawRectFilled(sf::FloatRect((elapsed3.asMilliseconds() - elapsed2.asMilliseconds()) * 50, 0, (elapsed1.asMilliseconds() - elapsed4.asMilliseconds()) * 50, 15), sf::Color(60, 255, 60));
                ImGui::End(); // end window

                App.clear(bgColor);

                elapsed2 = clock.getElapsedTime();
                App.draw(map);
                elapsed3 = clock.getElapsedTime();
                ImGui::SFML::Render(App);

                elapsed4 = clock.getElapsedTime();
                App.display();
        }
        map.save("saves/map.txt");
        ImGui::SFML::Shutdown();
}
