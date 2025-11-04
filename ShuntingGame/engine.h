#pragma once

#include <vector>

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

	virtual void Begin() { }
	virtual void Update() { }
	virtual void Draw() { }
	virtual void End() { }

	void AddGameObject(GameObject* gameObject);
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