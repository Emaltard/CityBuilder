#include "Event.h"

void handle_Events(sf::RenderWindow &App, Game &game,  TileMap &map, sf::View &view,  ImGuiIO &io)
{
        sf::Event Event;

        while (App.pollEvent(Event))
        {
                ImGui::SFML::ProcessEvent(Event);
                if (!io.WantCaptureMouse)
                {
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
                                        if (game.current_tile > -1)
                                        {
                                                game.selection_state = true;
                                                game.first_tile_selected = game.current_tile;
                                        }
                                }
                                if (Event.mouseButton.button == sf::Mouse::Right)
                                {
                                }
                                break;
                        case sf::Event::MouseButtonReleased:
                                if (Event.mouseButton.button == sf::Mouse::Left)
                                {
                                        game.selection_state = false;
                                        for (auto it = map.tiles_selected.begin(); it != map.tiles_selected.end(); ++it)
                                        {
                                                map.update(*it, game.type_id);
                                        }
                                        map.clear_tiles_selected();
                                }
                                break;
                        default:
                                break;
                        }
                }
        }
}
