#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "numericalVectors.h"

class Sprite
{
private:
	std::vector<sf::Sprite> layers;
	sf::Texture texture;

	sf::Vector2f position;
	sf::Angle rotation;

	float spacing;
	sf::Vector2f layerSize;
public:
	Sprite(std::string filePath, int sliceSize, float layerSpacing, sf::Vector2f initialPosition = sf::Vector2f(0.0f, 0.0f));
	Sprite() { }

	sf::Vector2f GetPosition() { return position; }
	void SetPosition(sf::Vector2f newPosition);
	void Move(sf::Vector2f movementToApply) { SetPosition(GetPosition() + movementToApply); }

	sf::Angle GetRotation() { return rotation; }
	void SetRotation(sf::Angle newRotation);

	void Draw();
};