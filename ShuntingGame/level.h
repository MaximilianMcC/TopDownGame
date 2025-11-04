#pragma once

#include <SFML/Graphics.hpp>

class Level
{
public:
	sf::View Camera;

	void Start();
	void Update();
	void Draw();
};