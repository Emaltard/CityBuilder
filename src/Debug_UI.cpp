#include "Debug_UI.h"

void ImGui_UI(sf::RenderWindow &App, Game &game, TileMap &map, sf::View &view, ImGuiIO &io, float imgui_color[3], int &map_size, int screen_x, int screen_y, int x, int y)
{

        ImGui::SFML::Update(App, game.deltaClock.restart());

        ImGui::Begin("Sample window"); // begin window

        // Background color edit
        if (ImGui::ColorEdit3("Background color", imgui_color))
        {
                // this code gets called if color value changes, so
                // the background color is upgraded automatically!
                game.change_bgColor(imgui_color[0], imgui_color[1], imgui_color[2]);
        }

        // Window title text edit
        if (ImGui::InputText("Window title", game.windowTitle, 255))
        {
                App.setTitle(game.windowTitle);
        }

        if (ImGui::Button("Reset View Position"))
        {
                view = App.getDefaultView();
                view.setCenter(32, map.get_tile_size().y * (map.get_map_size().x / 2));
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
                static int selected = game.selection_mode;
                if (ImGui::Selectable("Line", selected == 0, 0))
                {
                        selected = 0;
                        game.selection_mode = 0;
                }
                if (ImGui::Selectable("Rectangle", selected == 1, 0))
                {
                        selected = 1;
                        game.selection_mode = 1;
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
                                game.type_id = n;
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

        ImGui::Text("Tile Index: %d", game.current_tile);

        if (game.current_tile > -1)
        {
                ImGui::Text("Tile Type: %d", map.get_tile_type(game.current_tile));
        }
        else
        {
                ImGui::Text("Tile Type: None");
        }

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::Text("Mouse on ImGui window: %s", io.WantCaptureMouse ? "true" : "false");

        ImGui::End(); // end window
}