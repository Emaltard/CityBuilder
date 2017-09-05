#include <iostream>

#include <SFML/Graphics.hpp>

#include "map.hpp"

int main()
{
  sf::RenderWindow App(sf::VideoMode(800, 600, 32), "City Builder");
  App.setFramerateLimit(60);

  Map map = Map();

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
              break;

            case sf::Event::MouseButtonPressed:
              if(Event.mouseButton.button == sf::Mouse::Left){
                std::cout << Event.mouseButton.x << std::endl;
                std::cout << Event.mouseButton.y << std::endl;
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
