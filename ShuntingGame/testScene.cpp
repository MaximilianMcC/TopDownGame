#include "testScene.h"

#include "player.h"

void TestScene::Begin()
{
	// Zoom in the camera
	Camera.zoom(1.0f / 8.0f);

	// Add a player
	AddGameObject(new Player());
}