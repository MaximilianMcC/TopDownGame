#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

class InputHandler
{
private:
	static std::unordered_map<sf::Keyboard::Key, bool> previousKeyStates;

	static bool KeyPreviosulyPressed(sf::Keyboard::Key key);

public:
	static bool KeyPressed(sf::Keyboard::Key key);
	static bool KeyHeldDown(sf::Keyboard::Key key);

	static sf::Vector2f GetMousePosition();
};