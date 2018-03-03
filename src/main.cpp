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
        float color[3] = { 60.f/255.f, 60.f/255.f, 60.f/255.f };

        bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
        bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
        bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);

        sf::Clock deltaClock;
        char windowTitle[255] = "City Builder";

        TileMap map(sf::Vector2i(10,10), sf::Vector2i(64,32), "Media/tileset.png");
        map.load("saves/map.txt");

        sf::View view(sf::FloatRect(0, 0, 1280, 720));
        view.setCenter(0, 32 * (10 / 2));
        App.setView(view);

        int current_tile;

        while(App.isOpen())
        {
                sf::Event Event;

                // récupération de la position de la souris dans la fenêtre
                sf::Vector2i pixelPos = sf::Mouse::getPosition(App);

                // conversion en coordonnées "monde"
                sf::Vector2i position = (sf::Vector2i)App.mapPixelToCoords(pixelPos);

                int screen_x = position.x - 64/2;
                int screen_y = position.y;

                float y = (float(screen_x) / float(64/2) + float(screen_y) / float(32/2)) /2.0;
                float x = (float(screen_y) / float(32/2) -(float(screen_x) / float(64/2))) /2.0;
                if((x >= map.get_map_size().x) || (y >= map.get_map_size().y) || (x < 0) || (y < 0)) {
                        current_tile = -1;
                }else{
                        current_tile = (int)x * map.get_map_size().x + (int)y;
                }

                while(App.pollEvent(Event))
                {
                        ImGui::SFML::ProcessEvent(Event);
                        switch (Event.type)
                        {
                        case sf::Event::Closed:
                                App.close();
                                break;
                        case sf::Event::KeyPressed:
                                if (Event.key.code == sf::Keyboard::Escape)
                                {
                                        App.close();
                                }
                                if(Event.key.code == sf::Keyboard::Left) {
                                        view.move(-32, 0);
                                        App.setView(view);
                                }
                                if(Event.key.code == sf::Keyboard::Right) {
                                        view.move(32, 0);
                                        App.setView(view);
                                }
                                if(Event.key.code == sf::Keyboard::Up) {
                                        view.move(0, -32);
                                        App.setView(view);
                                }
                                if(Event.key.code == sf::Keyboard::Down) {
                                        view.move(0, 32);
                                        App.setView(view);
                                }
                                break;
                        case sf::Event::KeyReleased:
                                if(Event.key.code == sf::Keyboard::LControl) {
                                }
                                break;
                        case sf::Event::MouseButtonPressed:
                                if(Event.mouseButton.button == sf::Mouse::Left) {
                                        if(current_tile>-1) {
                                                map.update(current_tile, type_id);
                                        }
                                }
                                if(Event.mouseButton.button == sf::Mouse::Right) {
                                }
                                break;
                        default:
                                break;
                        }
                }

                ImGui::SFML::Update(App, deltaClock.restart());

                ImGui::Begin("Sample window"); // begin window

                // Background color edit
                if (ImGui::ColorEdit3("Background color", color)) {
                        // this code gets called if color value changes, so
                        // the background color is upgraded automatically!
                        bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
                        bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
                        bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
                }

                // Window title text edit
                if(ImGui::InputText("Window title", windowTitle, 255)) {
                        App.setTitle(windowTitle);
                }

                // if (ImGui::Button("Update window title")) {
                //      App.setTitle(windowTitle);
                // }

                // if(ImGui::InputInt("Map Size", &something)) {
                // }

                ImGui::Text("Map_size (width,height): %d, %d", map.get_map_size().x, map.get_map_size().y);

                if (ImGui::TreeNode("Tile Brush Type Selection"))
                {
                        static int selected = 0;
                        for (int n = 0; n < 4; n++)
                        {
                                char buf[32];
                                sprintf(buf, "Type %d", n);

                                if (ImGui::Selectable(buf, selected == n, 0)) {
                                        selected = n;
                                        type_id = n;
                                }
                        }
                        ImGui::TreePop();
                }

                if (ImGui::IsMousePosValid()) {
                        ImGui::Text("Mouse pos: (%d, %d)", screen_x, screen_y);
                }
                else
                        ImGui::Text("Mouse pos: <INVALID>");

                ImGui::Text("Tile (x,y): (%d, %d)", (int)x, (int)y);

                ImGui::Text("Tile Index: %d", current_tile);

                if(current_tile>-1) {
                        ImGui::Text("Tile Type: %d", map.get_tile_type(current_tile));
                }else{
                        ImGui::Text("Tile Type: None");
                }

                ImGui::End(); // end window

                App.clear(bgColor);

                App.draw(map);

                ImGui::SFML::Render(App);

                App.display();

        }
        map.save("saves/map.txt");
        ImGui::SFML::Shutdown();
}
