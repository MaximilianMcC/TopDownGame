#pragma once

#include <SFML/Graphics.hpp>
#include "utils.h"

class Block
{
private:
	bool isKey = false;
	Direction direction;
	sf::RectangleShape shape;

public:
	Block(sf::Vector2f position, int blockSize, Direction movementDirection, bool key = false);
	void Update();
	void Move();
	void Draw();
};