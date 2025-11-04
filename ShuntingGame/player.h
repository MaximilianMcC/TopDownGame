#pragma once

#include <SFML/Graphics.hpp>
#include "sprite.h"

class Player
{
private:
	Sprite* body = nullptr;
	float speed = 150.0f;

	void Move();
	void Rotate();
public:
	void Start();
	void Update();
	void Draw();
	void CleanUp();
};