#pragma once
#include "singleton.h"
class RenderManager : public singleton<RenderManager>
{
public :
	LPD3DXSPRITE sprite;
	RenderManager();
	~RenderManager();
	void Render3D(Mesh * mesh, Vec3 Pos,Vec3 Size,Vec3 Rot);
	void Render2D(Texture * text, Vec2 Pos, Vec2 Size, float rot);
	void UIRender(Texture * text ,Vec2 Pos ,Vec2 Size, float rot, D3DCOLOR color = D3DCOLOR_XRGB(255,255,255));
};
	

#define RENDER RenderManager::GetInstance()