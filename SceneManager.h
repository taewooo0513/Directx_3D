#pragma once
#include "Scene.h"
#include "singleton.h"
class SceneManager : public singleton<SceneManager>
{
public:
	SceneManager();
	~SceneManager();
public:
	Scene * NextScene = nullptr;
	Scene * NowScene = nullptr;

	map<string, Scene *> m_Scene;
	void AddScene(string key,Scene * scene);
	void ChangeScene(string key);
	void Update();
	void Render();
	void Release();
};

