#pragma once
#include "singleton.h"
#include "Object.h"
class Object;
class ObjectManager : public singleton<ObjectManager>
{
public:
	list<Object*> l_Obj[End];
	ObjectManager();
	~ObjectManager();
public:
	void AddObject(Object * obj , int Tag);
	void Update();
	void Render();
	void Release();
	void Collision(Object * obj);

};

