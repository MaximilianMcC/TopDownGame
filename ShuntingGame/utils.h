#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Utils
{
private:
	static sf::RenderWindow* window;
	static bool vsync;
	static float masterVolume;
	
public:
	static float DeltaTime;
	static sf::View Camera;

	static void Init(sf::RenderWindow* mainWindow)
	{
		// Assign the window and set the camera
		window = mainWindow;
		Camera = sf::View();
	}

	static sf::RenderWindow* GetWindow() { return window; }
	static void UseVsync(bool state);
	static bool VsyncOn();

	static void SetMasterVolume(float newMasterVolume);
	static void AddToMasterVolume(float change);
	static float GetMasterVolume();

	static std::vector<std::string> Split(std::string string, std::string delimiter);
	static bool StringEndsWith(std::string string, std::string ending);
	static void ReplaceAll(std::string& string, std::string thing, std::string with);

	static sf::Angle AngleFromVector(sf::Vector2f direction);
	static sf::Vector2f VectorFromAngle(sf::Angle angle);

	static sf::Color GetRandomColor();
};

enum Direction
{
	UP_AND_DOWN,
	SIDE_TO_SIDE
};