#include "engine.h"

#include "utils.h"

Scene* SceneManager::currentScene = nullptr;

void SceneManager::UnloadCurrentScene()
{
	// Unload everything
	for (size_t i = 0; i < currentScene->GameObjects.size(); i++)
	{
		currentScene->DestroyGameObject(currentScene->GameObjects[i]);
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

GameObject* Scene::AddGameObject(GameObject* gameObject)
{
	// Add and start the game object
	GameObjects.push_back(gameObject);
	GameObjects.back()->Start();

	// Give back the game object for
	// if we wanna do anything with it
	return GameObjects.back();
}

void Scene::DestroyGameObject(GameObject *gameObject)
{
	// Remove the game object from the list
	GameObjects.erase(std::remove(
		GameObjects.begin(),
		GameObjects.end(),
		gameObject
	), GameObjects.end());

	// Get rid of it
	gameObject->CleanUp();
	delete gameObject;
}
