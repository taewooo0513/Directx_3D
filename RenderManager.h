#pragma once
#include "singleton.h"
class RenderManager : public singleton<RenderManager>
{
private:
	struct sVerTexType
	{
		Vec3 m_pos;
		Vec2 m_uv;
		inline static constexpr DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX1;
	};
public :
	LPD3DXSPRITE sprite;
	RenderManager();
	~RenderManager();
	void Render3D(Mesh * mesh, Vec3 Pos,Vec3 Size,Vec3 Rot);
	void ShadowRender(Mesh * mesh ,Vec3 Pos,Vec3 Size,Vec3 Rot);
	void Render2D(Texture * text, Vec3 Pos, Vec2 Size, float rot);
	void UIRender(Texture * text ,Vec2 Pos ,Vec2 Size, float rot, D3DCOLOR color = D3DCOLOR_XRGB(255,255,255));
	void Begin();
	void End();
	void ResetDevice();
	void LostDevice();
	LPDIRECT3DVERTEXBUFFER9 m_vb;
	LPDIRECT3DINDEXBUFFER9 m_ib;
};
	

#define RENDER RenderManager::GetInstance()