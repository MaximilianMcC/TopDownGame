#include "testScene.h"

#include "player.h"

void TestScene::Begin()
{
	AddGameObject(new Player());
}