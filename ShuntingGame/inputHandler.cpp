#include "inputHandler.h"

#include "utils.h"

std::unordered_map<sf::Keyboard::Key, bool> InputHandler::previousKeyStates;

bool InputHandler::KeyPressed(sf::Keyboard::Key key)
{
	// Check for if the key state has changed since we last checked
	bool pressed = sf::Keyboard::isKeyPressed(key);
	bool previouslyPressed = previousKeyStates[key];

	// Update the keys new state
	previousKeyStates[key] = pressed;

	// For it to be pressed it must not
	// have been previously pressed
	return (pressed && (previouslyPressed == false));
}

bool InputHandler::KeyHeldDown(sf::Keyboard::Key key)
{
	// Check for if the key state has changed since we last checked
	bool pressed = sf::Keyboard::isKeyPressed(key);
	bool previouslyPressed = previousKeyStates[key];

	// Update the keys new state
	previousKeyStates[key] = pressed;

	// For it to be held it must
	// have been previously pressed
	return (pressed && previouslyPressed);
}

sf::Vector2f InputHandler::GetMousePosition()
{
	return Utils::GetWindow()->mapPixelToCoords(sf::Mouse::getPosition(*Utils::GetWindow()));
}

void InputHandler::CaptureInputs()
{
	// Loop over all keys and check for they are pressed or not
	//? Must use auto for a for loop like this in cpp
	for (auto& [key, _] : previousKeyStates)
	{
		previousKeyStates[key] = sf::Keyboard::isKeyPressed(key);
	}
}