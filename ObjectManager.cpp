#include "DXUT.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
	Release();
	for (int i = Begin; i < End; i++)
	{
		for (auto iter : l_Obj[i])
		{
			SAFE_DELETE(iter)
		}
		l_Obj[i].clear();
	}
}

void ObjectManager::AddObject(Object * obj, int Tag)
{
	if (obj)
		l_Obj[Tag].push_back(obj);
}

void ObjectManager::Update()
{
	for (int i = Begin; i < End; i++)
	{
		for (auto iter = l_Obj[i].begin(); iter != l_Obj[i].end();)
		{
			if ((*iter)->Destory == true)
			{
				(*iter)->Release();
				SAFE_DELETE((*iter));
				iter = l_Obj[i].erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}
}

void ObjectManager::Render()
{
	for (int i = Begin; i < End; i++)
	{
		for (auto iter : l_Obj[i])
		{
			iter->Render();
		}
	}
}

void ObjectManager::Release()
{
	for (int i = Begin; i < End; i++)
	{
		for (auto iter : l_Obj[i])
		{
			iter->Release();
		}
	}
}

void ObjectManager::Collision(Object * obj)
{
	for (auto Tag : obj->Act_Collide)
	{
		for (auto iter : l_Obj[Tag])
		{
			if (iter != obj)
			{
				float Dis = sqrt((obj->vector3.x - iter->vector3.x)*(obj->vector3.x - iter->vector3.x) + (obj->vector3.y - iter->vector3.y)*(obj->vector3.y - iter->vector3.y));
				if (Dis)
				{
					obj->CheckCollision(iter);
				}
			}
		}
	}
}
