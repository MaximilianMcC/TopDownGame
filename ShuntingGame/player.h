#pragma once

#include <SFML/Graphics.hpp>

class Player
{
private:
	sf::RectangleShape body;
	float speed = 150.0f;

	void Move();
	void Rotate();
public:
	void Start();
	void Update();
	void Draw();
};