#include "level.h"

#include "utils.h"

void Level::Draw()
{
	// Use the camera
	Utils::GetWindow()->setView(Camera);
}