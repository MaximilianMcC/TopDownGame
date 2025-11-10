#pragma once

#include <vector>
#include <string>
#include "block.h"

class Level
{
public:
	static std::vector<Block*> Blocks;
	static int Width;
	static int Height;
	
	static void Load(std::string path);
	static void Update();
	static void Draw();
	static void Unload();
};