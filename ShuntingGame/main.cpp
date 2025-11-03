#include <SFML/Graphics.hpp>
#include "utils.h"
#include "numericalVectors.h"
#include "assetManager.h"

int main()
{
	// SFML setup
	sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "basic as");
	sf::Clock deltaTimeClock = sf::Clock();

	// Load the debug font
	AssetManager::LoadDefaultFont("debug", "consola");

	// Share the window so we can draw and whatnot
	Utils::Init(&window);

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

		// Draw
		window.clear(sf::Color::Magenta);
		window.display();
	}

	return 0;
}