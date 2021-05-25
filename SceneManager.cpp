#include "DXUT.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	Release();
}

void SceneManager::AddScene(string key, Scene * scene)
{
	if (!scene)
		return;
	m_Scene[key] = scene;
}

void SceneManager::ChangeScene(string key)
{
	if(m_Scene[key])
	NextScene=m_Scene[key];
}

void SceneManager::Update()
{
	if (NextScene)
	{
		if (NowScene)
		{
			NowScene->Release();
		}
		NextScene = nullptr;
		NowScene = NextScene;
		NowScene->Init();
	}
	if (NowScene)
		NowScene->Update();
}

void SceneManager::Render()
{
	if (NowScene)
		NowScene->Render();
}

void SceneManager::Release()
{
	for (auto iter : m_Scene)
	{
		iter.second->Release();
		SAFE_DELETE(iter.second);
	}
	m_Scene.clear();
}
