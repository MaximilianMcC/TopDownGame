#pragma once

#include <SFML/Graphics.hpp>
#include "utils.h"

class Block
{
private:
	bool isKey = false;
	Direction direction;
	sf::RectangleShape shape;

	static bool OverlapsOnY(const sf::FloatRect& a, const sf::FloatRect& b);
	static bool OverlapsOnX(const sf::FloatRect& a, const sf::FloatRect& b);

public:
	Block(sf::Vector2f position, int blockSize, Direction movementDirection, bool key = false);
	void Update();
	void Move();
	void Draw();
};