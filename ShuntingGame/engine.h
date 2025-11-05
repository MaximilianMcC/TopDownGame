#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	virtual void Start() { }
	virtual void Update() { }
	virtual void Draw() { }
	virtual void CleanUp() { }
};

class Scene
{
public:
	std::vector<GameObject*> GameObjects;
	sf::View Camera;

	virtual void Begin() { }
	virtual void Update() { }
	virtual void Draw() { }
	virtual void End() { }

	// TODO: Put this in scene manager because its less typing
	GameObject* AddGameObject(GameObject* gameObject);
	void DestroyGameObject(GameObject* gameObject);
};

class SceneManager
{
private:
	static Scene* currentScene;

	static void UnloadCurrentScene();
public:
	static Scene* GetScene() { return currentScene; }
	static void SetScene(Scene* newScene);
	
	static void Update();
	static void Draw();
	static void CleanUp();
};