#include <SFML/Graphics.hpp>
#include "utils.h"
#include "assetManager.h"
#include "block.h"

int main()
{
	// SFML setup
	sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "In America they spell Pyjamas like Pajamas");
	sf::Clock deltaTimeClock = sf::Clock();

	// Load the debug font
	//AssetManager::LoadDefaultFont("debug", "consola");

	// Share the window so we can draw and whatnot
	Utils::Init(&window);


	//! debug
	Block* block1 = new Block(sf::Vector2f(1.0f, 1.0f), 2, SIDE_TO_SIDE);
	Block* block2 = new Block(sf::Vector2f(2.0f, 3.0f), 3, SIDE_TO_SIDE, true);


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
		block1->Draw();
		block2->Draw();
		window.display();
	}

	delete block1;
	delete block2;

	return 0;
}