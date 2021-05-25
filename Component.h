#pragma once
class Object;
class Component
{
public:
	Component();
	virtual ~Component();
public:
	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
	virtual void OnCollision(Object* _Other,float Dis);
	Object * obj;
	template<typename T>
	T* AddComponent()
	{
		return obj->AddComponent<T>();
	}

	template<typename T>
	T* GetComponent()
	{
		return obj->GetComponent<T>();
	}
};

