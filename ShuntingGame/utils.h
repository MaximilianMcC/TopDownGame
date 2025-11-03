#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Utils
{
private:
	static sf::RenderWindow* window;
	
public:
	static float DeltaTime;

	static void Init(sf::RenderWindow* mainWindow)
	{
		window = mainWindow;
	}

	static sf::RenderWindow* GetWindow() { return window; }

	static std::vector<std::string> Split(std::string string, std::string delimiter);
	static bool StringEndsWith(std::string string, std::string ending);

	static sf::Vector2f GetMousePosition();

	static sf::Color GetRandomColor();
};