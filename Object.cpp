#include "DXUT.h"
#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::Init()
{
}

void Object::Update()
{
	for (auto & iter : components)
	{
		iter->Update();
	}
}

void Object::Render()
{
	for (auto & iter : components)
	{
		iter->Render();
	}
}

void Object::Release()
{
}

void Object::CheckCollision(Object * obj)
{
	
}


