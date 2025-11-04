#include "engine.h"

#include "utils.h"

Scene* SceneManager::currentScene = nullptr;

void SceneManager::UnloadCurrentScene()
{
	// Unload everything
	for (size_t i = 0; i < currentScene->GameObjects.size(); i++)
	{
		currentScene->GameObjects[i]->CleanUp();
		delete currentScene->GameObjects[i];
		currentScene->GameObjects[i] = nullptr;
	}
	
	// Delete the scene
	currentScene->End();
	delete currentScene;
	currentScene = nullptr;
}

void SceneManager::SetScene(Scene *newScene)
{
	// If we had a previous scene then unload it
	if (currentScene != nullptr) UnloadCurrentScene();

	// Load the new scene
	currentScene = newScene;
	currentScene->Begin();
}

void SceneManager::Update()
{
	// Update everything
	for (size_t i = 0; i < currentScene->GameObjects.size(); i++)
	{
		currentScene->GameObjects[i]->Update();
	}

	currentScene->Update();
}

void SceneManager::Draw()
{
	// Use the camera
	Utils::GetWindow()->setView(currentScene->Camera);

	// Draw everything automatically
	for (size_t i = 0; i < currentScene->GameObjects.size(); i++)
	{
		currentScene->GameObjects[i]->Draw();
	}

	// Draw everything manually
	currentScene->Draw();
}

void SceneManager::CleanUp()
{
	UnloadCurrentScene();
}

void Scene::AddGameObject(GameObject* gameObject)
{
	gameObject->Start();
	GameObjects.push_back(gameObject);
}
