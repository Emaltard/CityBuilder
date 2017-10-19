#include <iostream>

#include <SFML/Graphics.hpp>

#include "map.hpp"

int main()
{
        sf::RenderWindow App(sf::VideoMode(800, 600, 32), "City Builder");
        App.setFramerateLimit(30);

        Map map(10);

        bool ctrl_hold = false;

        while(App.isOpen())
        {
                sf::Event Event;
                while(App.pollEvent(Event))
                {
                        // on regarde le type de l'évènement...
                        switch (Event.type)
                        {
                        // fenêtre fermée
                        case sf::Event::Closed:
                                App.close();
                                break;

                        // touche pressée
                        case sf::Event::KeyPressed:
                                if (Event.key.code == sf::Keyboard::Escape)
                                {
                                        App.close();
                                }
                                else if(Event.key.code == sf::Keyboard::LControl) {
                                        ctrl_hold = true;
                                }
                                break;
                        case sf::Event::KeyReleased:
                                if(Event.key.code == sf::Keyboard::LControl) {
                                        ctrl_hold = false;
                                }
                                break;

                        case sf::Event::MouseButtonPressed:
                                if(Event.mouseButton.button == sf::Mouse::Left) {
                                        if(!ctrl_hold) {
                                                for(std::vector<Tile*>::iterator it = map.tiles_selected.begin(); it != map.tiles_selected.end(); ++it) {
                                                        (*it)->sprite.setColor(sf::Color(255, 255, 255));
                                                }
                                                map.tiles_selected.clear();
                                        }
                                        sf::Vector2i coord_map = map.screen_to_map(sf::Vector2i(Event.mouseButton.x, Event.mouseButton.y));
                                        map.select_tile(coord_map);
                                }
                                break;

                        // on ne traite pas les autres types d'évènements
                        default:
                                break;
                        }
                }

                App.clear();

                App.draw(map);

                App.display();
        }
}
