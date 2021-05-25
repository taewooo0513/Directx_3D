#include "DXUT.h"
#include "RenderManager.h"

RenderManager::RenderManager()
{
	D3DXCreateSprite(Device, &sprite);

	Device->SetRenderState(D3DRS_LIGHTING,FALSE);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
}

RenderManager::~RenderManager()
{
	sprite->Release();
	
}

void RenderManager::Render3D(Mesh * mesh, Vec3 Pos, Vec3 Size, Vec3 Rot)
{
	D3DXMATRIXA16 matP, matS, matR, matW;
	D3DXMATRIXA16 matX, matY, matZ;

	D3DXMatrixTranslation(&matP, Pos.x, Pos.y, 0);
	D3DXMatrixScaling(&matS, Size.x, Size.y, Size.z);
	D3DXMatrixRotationX(&matX, Rot.x);
	D3DXMatrixRotationY(&matY, Rot.y);
	D3DXMatrixRotationZ(&matZ, Rot.z);

	matR = matX * matY*matZ;
	matW = matR * matP * matS;
	Device->SetTransform(D3DTS_WORLD, &matW);
	for (int i = 0; i < mesh->materials.size(); i++)
	{
		Device->SetTexture(0, mesh->materials[i]->pTexture);
		mesh->mesh->DrawSubset(i);
	}
}

void RenderManager::Render2D(Texture * text, Vec2 Pos, Vec2 Size, float rot)
{
	D3DXMATRIXA16 matP, matS, matR, matW;
	D3DXMatrixTranslation(&matP, Pos.x, Pos.y, 0);
	D3DXMatrixScaling(&matS, Size.x, Size.y, 1);
	D3DXMatrixRotationZ(&matR, rot);
	matW = matR * matP * matS;
	Device->SetTransform(D3DTS_WORLD, &matW);
	Device->SetTexture(0, text->texturePtr);
}

void RenderManager::UIRender(Texture * text, Vec2 Pos, Vec2 Size, float rot, D3DCOLOR color)
{
	D3DXMATRIXA16 mat;
	D3DXMatrixTransformation2D(&mat, nullptr, 0, &Size, nullptr, 0, &Pos);
	sprite->SetTransform(&mat);
	sprite->Draw(text->texturePtr, nullptr, &Vec3(text->info.Width / 2, text->info.Height / 2, 0.1f), nullptr, color);
}
