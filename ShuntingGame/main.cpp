#include <SFML/Graphics.hpp>
#include "utils.h"
#include "assetManager.h"
#include "level.h"
#include "configManager.h"
#include "debugger.h"

int main()
{
	// SFML setup
	sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "graphics and oop do not mix");
	sf::Clock deltaTimeClock = sf::Clock();

	// Load random assets
	AssetManager::LoadDefaultFont("arial", "ARIAL");
	AssetManager::LoadDefaultFont("consolas", "consola");

	// Window kinda setup
	Utils::Init(&window);
	ConfigManager::Init();
	Debugger::Start();

	// Load the level
	Level::Load(ConfigManager::GetString("level"));

	// Zoom in the camera a little
	Utils::Camera.zoom(1.0f / 3.0f);

	// Game window
	while (window.isOpen())
	{
		// Calculate and update delta time
		// and do the debug stuff
		Utils::DeltaTime = deltaTimeClock.restart().asSeconds();
		Debugger::Update();

		// Check for any events
		while (const std::optional event = window.pollEvent())
		{
			// Check for if we wanna close the window
			if (event->is<sf::Event::Closed>()) window.close();

			// Check for if we resize the window
			if (event->is<sf::Event::Resized>())
			{
				// Update the size in the config
				ConfigManager::SetInt("windowX", (int)window.getSize().x);
				ConfigManager::SetInt("windowY", (int)window.getSize().y);
			}
		}
		
		// Update
		Level::Update();
		
		// Draw
		window.clear(sf::Color(0x778396));
		window.setView(Utils::Camera);
		Level::Draw();
		Debugger::Draw();
		window.display();
	}

	Level::Unload();
	Debugger::CleanUp();

	return 0;
}