#include <iostream>
#include "map.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

int main()
{
	sf::RenderWindow App(sf::VideoMode(1280, 770, 32), "City Builder");
	App.setFramerateLimit(60);
	ImGui::CreateContext();
	ImGui::SFML::Init(App);

	std::ifstream file("map.txt");
	Map* map;
	int map_size = 10;
	if(file.is_open()) {
		map = new Map(file);
		map_size = map->get_map_size();
	}
	else{
		map = new Map(map_size);
	}



	bool ctrl_hold = false;
	int type_id = 0;

	sf::Color bgColor;
	float color[3] = { 33.f/255.f, 33.f/255.f, 33.f/255.f };
	sf::Clock deltaClock;
	char windowTitle[255] = "ImGui + SFML = <3";

	while(App.isOpen())
	{
		sf::Event Event;
		while(App.pollEvent(Event))
		{
			ImGui::SFML::ProcessEvent(Event);
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

		if(ImGui::InputInt("Map Size", &map_size)) {
			map->change_map_size(map_size);
			map_size = map->get_map_size();
		}

		if (ImGui::TreeNode("Tile Brush Type Selection"))
		{
			static int selected = 0;
			for (int n = 0; n < 2; n++)
			{
				char buf[32];
				sprintf(buf, "Type %d", n);
				if (ImGui::Selectable(buf, selected == n, 0, ImVec2(50,50))) {
					selected = n;
					type_id = n+1;
				}
				if ((n % 2) < 1) ImGui::SameLine();
			}
			ImGui::TreePop();
		}

		ImGuiIO& io = ImGui::GetIO();
		if (ImGui::IsMousePosValid())
			ImGui::Text("Mouse pos: (%g, %g)", io.MousePos.x, io.MousePos.y);
		else
			ImGui::Text("Mouse pos: <INVALID>");



		ImGui::End(); // end window

		App.clear(bgColor);

		App.draw(*map);

		ImGui::SFML::Render(App);

		App.display();

	}

	ImGui::SFML::Shutdown();
}
