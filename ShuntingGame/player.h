#pragma once

#include <SFML/Graphics.hpp>
#include "sprite.h"
#include "engine.h"

class Player : public GameObject
{
private:
	Sprite* body = nullptr;
	float speed = 150.0f;

	void Move();
	void Rotate();
	void Shoot();
public:
	void Start() override;
	void Update() override;
	void Draw() override;
	void CleanUp() override;
};