#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "block.h"

class Level
{
private:
	static sf::Text* levelNameText;
public:
	static std::vector<Block*> Blocks;
	static int Width;
	static int Height;
	
	// TODO: Use a definition for this instead
	const static int BlockSize;
	
	static sf::RectangleShape Border;
	static std::string Name;
public:	
	static void Load(std::string path);
	static void Update();
	static void Draw();
	static void Unload();
};