#include "utils.h"
#include <cstdlib>
#include "configManager.h"

// Register private static stuff
sf::RenderWindow* Utils::window;
bool Utils::vsync;
float Utils::masterVolume = 50.0f;

// Register public static stuff
float Utils::DeltaTime;
sf::View Utils::Camera;

void Utils::UseVsync(bool state)
{
	vsync = state;
	window->setVerticalSyncEnabled(vsync);
	ConfigManager::SetBoolean("vsync", vsync);
}

bool Utils::VsyncOn()
{
	return vsync;
}

void Utils::SetMasterVolume(float newMasterVolume)
{
	// Ensure the volume is between 0 and 100
	masterVolume = std::clamp(newMasterVolume, 0.0f, 100.0f);
	ConfigManager::SetFloat("volume", masterVolume);
}

void Utils::AddToMasterVolume(float change)
{
	SetMasterVolume(masterVolume + change);
}

float Utils::GetMasterVolume()
{
	return masterVolume;
}

std::vector<std::string> Utils::Split(std::string string, std::string delimiter)
{
	std::vector<std::string> splitString;
	std::string currentToken;
 
	// Loop over every every character in the string
	for (size_t i = 0; i < string.length(); i++)
	{
		// Add the current character to our 'delimiter checker'
		currentToken += string[i];
 
		// Check for if we've got a full delimiter
		if (StringEndsWith(currentToken, delimiter) == false) continue;
 
		// Our delimiter string ends with the delimiter.
		// Remove the delimiter from the token, and add
		// it to the list to be returned
		currentToken.erase(currentToken.length() - delimiter.length());
		splitString.push_back(currentToken);
 
		// Reset the token for next time
		currentToken.clear();
	}
 
	// Add whatever we're left with to the
	// list of split things if we've already
	// found more than one split
	if (splitString.size() != 0) splitString.push_back(currentToken);

	// If there was nothing then return the whole string
	if (splitString.size() == 0) splitString.push_back(string);
 
	// Give back the string
	return splitString;
}
 
bool Utils::StringEndsWith(std::string string, std::string ending)
{
	// The ending must be able to 'fit' inside
	// the string it's being searched for in
	if (ending.length() > string.length()) return false;
 
	// 'trim' the string and check for if
	// the end string is in it
	return (string.compare(
		string.length() - ending.length(),
		ending.length(),
		ending
	) == 0);
}

// TODO: Rename these parameters because what is that bruh
void Utils::ReplaceAll(std::string& string, std::string thing, std::string with)
{
	//? I lowk don't know how this works
	size_t index = 0;
	while ((index = string.find(thing, index)) != std::string::npos)
	{
		string.replace(index, thing.length(), with);
		index += with.length();
	}
}

sf::Angle Utils::AngleFromVector(sf::Vector2f direction)
{
	return sf::radians(std::atan2(direction.y, direction.x));
}

sf::Vector2f Utils::VectorFromAngle(sf::Angle angle)
{
	float radians = angle.asRadians();
	return sf::Vector2f(std::cos(radians), std::sin(radians));
}

sf::Color Utils::GetRandomColor()
{
	// TODO: Seed it
	return sf::Color(
		std::rand() % 256,
		std::rand() % 256,
		std::rand() % 256
	);
}