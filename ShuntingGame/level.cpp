#include "level.h"

//? I hate cpp
std::vector<Block*> Level::Blocks;

void Level::Load()
{
	// Clear any previous stuff
	Blocks.clear();

	// TODO: Load from file
	Blocks.push_back(new Block(sf::Vector2f(1.0f, 1.0f), 2, SIDE_TO_SIDE));
	Blocks.push_back(new Block(sf::Vector2f(2.0f, 3.0f), 3, UP_AND_DOWN, true));
}

void Level::Update()
{
	// Loop over all blocks and update
	for (size_t i = 0; i < Blocks.size(); i++)
	{
		Blocks[i]->Update();
	}
}

void Level::Draw()
{
	// Loop over all blocks and draw
	for (size_t i = 0; i < Blocks.size(); i++)
	{
		Blocks[i]->Draw();
	}
}

void Level::Unload()
{
	for (size_t i = 0; i < Blocks.size(); i++)
	{
		delete Blocks[i];
		Blocks[i] = nullptr;
	}
	Blocks.clear();
}
