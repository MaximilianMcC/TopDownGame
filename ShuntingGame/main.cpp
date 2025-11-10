#include <SFML/Graphics.hpp>
#include "utils.h"
#include "assetManager.h"
#include "level.h"

int main()
{
	// SFML setup
	sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "In America they spell Pyjamas like Pajamas");
	sf::Clock deltaTimeClock = sf::Clock();

	// Share the window so we can draw and whatnot
	Utils::Init(&window);

	Level::Load();

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
		window.clear(sf::Color::Magenta);
		Level::Draw();
		window.display();
	}

	Level::Unload();

	return 0;
}