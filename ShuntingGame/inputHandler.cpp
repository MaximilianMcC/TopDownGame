#include "inputHandler.h"

#include "utils.h"

std::unordered_map<sf::Keyboard::Key, bool> InputHandler::previousKeyStates;

bool InputHandler::KeyPreviosulyPressed(sf::Keyboard::Key key)
{
	// Loop over all previous keys
	std::unordered_map<sf::Keyboard::Key, bool>::iterator iterator;
	iterator = previousKeyStates.find(key);

	// Check for if the key exists
	if (iterator != previousKeyStates.end())
	{
		// Get its state
		return iterator->second;
	}

	return false;
}

bool InputHandler::KeyPressed(sf::Keyboard::Key key)
{
	// Check for if its pressed
	bool downRn = sf::Keyboard::isKeyPressed(key);
	bool previouslyDown = KeyPreviosulyPressed(key);

	// Update the stored state
	previousKeyStates[key] = downRn;

	// To be pressed then it needs to
	// not have been previously pressed
	return (downRn && (previouslyDown == false));
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