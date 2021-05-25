#pragma once
#include "Component.h"
class Object abstract
{
public:
	Object();
	virtual ~Object();
public:
	Vec2 vector2,size2;
	Vec3 vector3,size3, rot3;
	float rot;
	
	list<Component *> components;
	vector<int> Act_Collide;
	void Init();
	void Update();
	void Render();
	void Release();
	void CheckCollision(Object * obj);
	template<typename T>
	T* AddComponent()
	{
		T* a = new T;
		a->obj = this;
		m_Components.push_back(a);
		a->Init();
		return a;
	}
	bool Destory = false;
	template<typename T>
	T* GetComponent()
	{
		for (auto& iter : m_Components)
		{
			if (typeid(*iter) == typeid(T))
			{
				return static_cast<T*>(iter);
			}
		}

		T* Cast;
		for (auto& iter : m_Components)
		{
			Cast = dynamic_cast<T*>(iter);
			if (Cast != nullptr)
			{
				return Cast;
			}
		}
		return nullptr;
	}
};

