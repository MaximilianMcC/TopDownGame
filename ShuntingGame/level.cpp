#include "level.h"

#include <iostream>
#include <fstream>
#include "utils.h"

//? I hate cpp
std::vector<Block*> Level::Blocks;
int Level::Width = 0;
int Level::Height = 0;
const int Level::BlockSize = 16;

void Level::Load(std::string path)
{
	// Clear any previous stuff
	Blocks.clear();
	Width = 0;
	Height = 0;

	// Open the level file
	std::ifstream file(path);
	if (!file)
	{
		std::cerr << "issue loading level at " << path << "\n";
		return;
	}

	// Loop over every line in the file
	std::string line;
	bool gotSize = false;
	sf::Vector2f position;
	while (std::getline(file, line))
	{
		// The first line is the maps size
		if (gotSize == false)
		{
			// Extract the width and height automatically
			std::vector<std::string> data = Utils::Split(line, "x");
			Width = std::stoi(data[0]);
			Height = std::stoi(data[1]);

			gotSize = true;
			continue;
		}

		// Extract all blocks in the line
		std::vector<std::string> blockData = Utils::Split(line, "}{");
		for (std::string& block : blockData)
		{
			// Remove the front/back things
			Utils::ReplaceAll(block, "{", "");
			Utils::ReplaceAll(block, "}", "");

			// Get the direction that the block faces (+ check if its real)
			Direction direction;
			if (block._Starts_with("u")) direction = UP_AND_DOWN;
			else if (block._Starts_with("s")) direction = SIDE_TO_SIDE;
			else
			{
				// We're just looking at a space. Ignore it
				// TODO: Guard clause because this is really bad
				position.x++;
				continue;
			}

			// Get rid of the direction character since its been 'used'
			block.erase(0, 1);

			// Get the size of the block (only ever 1 chracter because im lazy)
			// TODO: Don't do this cheap as crook as way of converting
			int size = block[0] - '0';
			block.erase(0, 1);

			// Check for if this is the key
			bool key = block._Starts_with("k");

			// Now that we have everything, make the actual block
			Block* newBlock = new Block(position, size, direction, key);
			Blocks.push_back(newBlock);

			// Increase the X for the next block
			position.x++;
		}

		// Increase the X for the next row of blocks
		position.y++;
	}
	file.close();
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
