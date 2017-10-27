#include <iostream>
#include <SFML/Graphics.hpp>
#include "map.hpp"

int main()
{
        sf::RenderWindow App(sf::VideoMode(800, 600, 32), "City Builder");
        App.setFramerateLimit(60);

        std::ifstream file("map.txt");
        Map* map;
        if(file.is_open()) {
                map = new Map(file);
        }
        else{
                map = new Map(10);
        }

        sf::Sprite ui_grass;
        sf::Sprite ui_water;
        sf::RectangleShape rectangle(sf::Vector2f(800, 100));
        sf::RectangleShape rectangle1(sf::Vector2f(84, 90));
        sf::RectangleShape rectangle2(sf::Vector2f(84, 90));

        rectangle.setFillColor(sf::Color(33,33,33));
        rectangle.setPosition(0,500);
        rectangle.setOutlineColor(sf::Color(0,61,51));
        rectangle.setOutlineThickness(-5);

        rectangle1.setFillColor(sf::Color::Transparent);
        rectangle1.setPosition(5,505);

        rectangle2.setFillColor(sf::Color::Transparent);
        rectangle2.setPosition(89,505);




        ui_grass.setTexture(map->texture_vector[0]);
        ui_water.setTexture(map->texture_vector[1]);

        ui_grass.setPosition(15,525);
        ui_water.setPosition(99,525);

        for (auto it = begin (map->texture_vector); it != end (map->texture_vector); ++it) {

        }

        bool ctrl_hold = false;
        int type_id = 0;

        while(App.isOpen())
        {
                sf::Event Event;
                while(App.pollEvent(Event))
                {
                        switch (Event.type)
                        {
                        case sf::Event::Closed:
                                map->save();
                                App.close();
                                break;
                        case sf::Event::KeyPressed:
                                if (Event.key.code == sf::Keyboard::Escape)
                                {
                                        map->save();
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
                                                for(std::vector<Tile*>::iterator it = map->tiles_selected.begin(); it != map->tiles_selected.end(); ++it) {
                                                        (*it)->sprite.setColor(sf::Color(255, 255, 255));
                                                }
                                                map->tiles_selected.clear();


                                                if(Event.mouseButton.y>500 && Event.mouseButton.y<600) {
                                                        if(Event.mouseButton.x>5 && Event.mouseButton.x<89) {
                                                                rectangle2.setFillColor(sf::Color::Transparent);
                                                                rectangle1.setFillColor(sf::Color(0,105,92));
                                                                type_id = 1;
                                                        }
                                                        if(Event.mouseButton.x>89 && Event.mouseButton.x<173) {
                                                                rectangle1.setFillColor(sf::Color::Transparent);
                                                                rectangle2.setFillColor(sf::Color(0,105,92));
                                                                type_id = 2;
                                                        }
                                                }
                                        }else if(Event.mouseButton.y<500) {
                                                sf::Vector2i coord_map = map->screen_to_map(sf::Vector2i(Event.mouseButton.x, Event.mouseButton.y));
                                                map->select_tile(coord_map);
                                        }

                                }
                                if(Event.mouseButton.button == sf::Mouse::Right) {
                                        if(Event.mouseButton.y<500) {
                                                if(type_id) {
                                                        sf::Vector2i coord_map = map->screen_to_map(sf::Vector2i(Event.mouseButton.x, Event.mouseButton.y));
                                                        map->set_tile_type(coord_map, type_id);
                                                }
                                        }
                                }
                                break;
                        default:
                                break;
                        }
                }

                App.clear();

                App.draw(*map);
                App.draw(rectangle);
                App.draw(rectangle1);
                App.draw(rectangle2);

                ui_water.setColor(sf::Color(0,0,0,50));
                ui_water.setPosition(ui_water.getPosition().x+2, ui_water.getPosition().y+3);
                App.draw(ui_water);
                ui_water.setColor(sf::Color::White);
                ui_water.setPosition(ui_water.getPosition().x-2, ui_water.getPosition().y-3);
                App.draw(ui_water);

                ui_grass.setColor(sf::Color(0,0,0,50));
                ui_grass.setPosition(ui_grass.getPosition().x+2, ui_grass.getPosition().y+3);
                App.draw(ui_grass);
                ui_grass.setColor(sf::Color::White);
                ui_grass.setPosition(ui_grass.getPosition().x-2, ui_grass.getPosition().y-3);
                App.draw(ui_grass);

                App.display();

        }
}
