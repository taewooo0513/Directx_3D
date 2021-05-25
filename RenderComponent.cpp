#include "DXUT.h"
#include "RenderComponent.h"

RenderComponent::RenderComponent()
{
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::Init()
{
}

void RenderComponent::Update()
{
}

void RenderComponent::Render()
{
	if (mesh)
	{
		Render3D();
	}
	if (text)
	{
		Render2D();
	}
}

void RenderComponent::Release()
{
}

void RenderComponent::Render3D()
{
	RENDER->Render3D(mesh, obj->vector3, obj->size3, obj->rot3);
}

void RenderComponent::Render2D()
{
	RENDER->Render2D(text,obj->vector3,obj->size2,obj->rot);
}
