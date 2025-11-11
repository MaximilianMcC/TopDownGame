#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

class InputHandler
{
private:
	static std::unordered_map<sf::Keyboard::Key, bool> previousKeyStates;

public:
	static bool KeyPressed(sf::Keyboard::Key key);
	static bool KeyHeldDown(sf::Keyboard::Key key);

	static sf::Vector2f GetMousePosition();

	static void CaptureInputs();
};