#pragma once

#include <SFML/Graphics.hpp>
#include "engine.h"

class Projectile : public GameObject
{
private:
	sf::RectangleShape body;
	float speed = 10.0f;
public:
	void Start() override;
	void Update() override;
	void Draw() override;

	void Init(sf::Vector2f position, sf::Angle direction);
};