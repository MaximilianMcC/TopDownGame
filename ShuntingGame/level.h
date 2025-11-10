#pragma once

#include <vector>
#include "block.h"

class Level
{
public:
	static std::vector<Block*> Blocks;
	
	static void Load();
	static void Update();
	static void Draw();
	static void Unload();
};