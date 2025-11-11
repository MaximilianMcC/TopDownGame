#include <SFML/Graphics.hpp>
#include "utils.h"
#include "assetManager.h"
#include "level.h"

int main()
{
	// SFML setup
	sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "graphics and oop do not mix");
	sf::Clock deltaTimeClock = sf::Clock();

	// Share the window so we can draw and whatnot
	Utils::Init(&window);

	Level::Load("./assets/levels/1.txt");

	// Zoom in the camera a little
	Utils::Camera.zoom(1.0f / 3.0f);

	// Game window
	while (window.isOpen())
	{
		// Calculate and update delta time
		Utils::DeltaTime = deltaTimeClock.restart().asSeconds();

		// Check for any events
		while (const std::optional event = window.pollEvent())
		{
			// Check for if we wanna close the window
			if (event->is<sf::Event::Closed>()) window.close();
		}
		
		// Update
		Level::Update();
		
		// Draw
		window.clear(sf::Color(0x778396));
		window.setView(Utils::Camera);
		Level::Draw();
		window.display();
	}

	Level::Unload();

	return 0;
}