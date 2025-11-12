#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "utils.h"

class Block
{
private:
	bool isKey = false;
	Direction direction;
	sf::RectangleShape shape;

	static sf::Sound* levelCompleteSound;

	static bool OverlapsOnY(const sf::FloatRect& a, const sf::FloatRect& b);
	static bool OverlapsOnX(const sf::FloatRect& a, const sf::FloatRect& b);

public:

	static void Load();
	static void UnLoad();
	Block(sf::Vector2f position, int blockSize, Direction movementDirection, bool key = false);

	void Update();
	void Move();
	void Draw();
};