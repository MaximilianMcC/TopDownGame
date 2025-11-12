#pragma once

#include <SFML/Graphics.hpp>

class Debugger
{
private:
	static sf::Text* text;
	static sf::RectangleShape background;

public:
	static bool Enabled;

	static void Start();
	static void Update();
	static void Draw();
	static void CleanUp();
};