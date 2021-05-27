#include "DXUT.h"
#include "RenderManager.h"

RenderManager::RenderManager()
{
	D3DXCreateSprite(Device, &sprite);
	Device->CreateVertexBuffer(sizeof(sVerTexType) * 4, D3DUSAGE_WRITEONLY, sVerTexType::FVF, D3DPOOL_DEFAULT, &m_vb, NULL);

	sVerTexType* pVertices = nullptr;

	m_vb->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].m_pos = D3DXVECTOR3(-0.5f, 0.5f, 0.f);
	pVertices[1].m_pos = D3DXVECTOR3(0.5f, 0.5f, 0.f);
	pVertices[2].m_pos = D3DXVECTOR3(-0.5f, -0.5f, 0.f);
	pVertices[3].m_pos = D3DXVECTOR3(0.5f, -0.5f, 0.f);

	//0   1
	//
	//2 3

	pVertices[0].m_uv = D3DXVECTOR2(0, 0);
	pVertices[1].m_uv = D3DXVECTOR2(1, 0);
	pVertices[2].m_uv = D3DXVECTOR2(0, 1);
	pVertices[3].m_uv = D3DXVECTOR2(1, 1);

	m_vb->Unlock();

	Device->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_ib, NULL);

	WORD idx[] = { 1, 2, 0, 1, 3, 2 };

	void* pIndices = NULL;

	m_ib->Lock(0, 0, &pIndices, 0);
	memcpy(pIndices, idx, sizeof(WORD) * 6);
	m_ib->Unlock();
	//--빌보딩용 버퍼 생성

	//빌보딩용 버퍼 적용
	Device->SetStreamSource(0, m_vb, 0, sizeof(sVerTexType));
	Device->SetFVF(sVerTexType::FVF);
	Device->SetIndices(m_ib);

	Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
}

RenderManager::~RenderManager()
{
	sprite->Release();
	m_ib->Release();
	m_vb->Release();
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

void RenderManager::ShadowRender(Mesh * mesh, Vec3 Pos, Vec3 Size, Vec3 Rot)
{
	D3DXMATRIXA16 matP, matS, matR, matW;
	D3DXMATRIXA16 matX, matY, matZ,matProj,matV;

	D3DXMatrixTranslation(&matP, Pos.x, Pos.y, Pos.z);
	D3DXMatrixScaling(&matS, Size.x, Size.y, Size.z);
	D3DXMatrixRotationX(&matX, Rot.x);
	D3DXMatrixRotationY(&matY, Rot.y);
	D3DXMatrixRotationZ(&matZ, Rot.z);
	Device->GetTransform(D3DTS_PROJECTION, &matProj);
	Device->GetTransform(D3DTS_VIEW, &matV);

	matR = matX * matY*matZ;
	matW = matR * matP * matS;
	Device->SetTransform(D3DTS_WORLD, &matW);
	Vec3 LightPos = Vec3(0, 0, 0);
	Vec3 Normal;
	D3DXVec3Normalize(&Normal,&Vec3(LightPos - Pos));
	LOADER->m_effect["Shadow"]->SetValue((D3DXHANDLE)"LightDir",Normal,sizeof(Vec3));
	LOADER->m_effect["Shadow"]->SetValue((D3DXHANDLE)"LightColor",D3DXVECTOR4(1.f,1.f,1.f,1.f),sizeof(D3DXVECTOR4));
	LOADER->m_effect["Shadow"]->SetMatrix((D3DXHANDLE)"matW", &(matW));
	LOADER->m_effect["Shadow"]->SetMatrix((D3DXHANDLE)"ViewProjMatrix", &(matV*matProj));
	LOADER->m_effect["Shadow"]->Begin(0,0);
	for (int i = 0; i < mesh->materials.size(); i++)
	{
		LOADER->m_effect["Shadow"]->BeginPass(i);
		
		LOADER->m_effect["Shadow"]->SetTexture((D3DXHANDLE)"MeshText",mesh->materials[i]->pTexture);
		LOADER->m_effect["Shadow"]->CommitChanges();

		Device->SetTexture(0, mesh->materials[i]->pTexture);
		mesh->mesh->DrawSubset(i);
		LOADER->m_effect["Shadow"]->EndPass();
	}
	LOADER->m_effect["Shadow"]->End();
}

void RenderManager::Render2D(Texture * text, Vec3 Pos, Vec2 Size, float rot)
{
	D3DXMATRIXA16 matP, matS, matR, matW;
	D3DXMatrixTranslation(&matP, Pos.x, Pos.y, Pos.z);
	D3DXMatrixScaling(&matS,text->info.Width/100, text->info.Height/100, 0.01);
	D3DXMatrixRotationZ(&matR, rot);
	matW = matR *matS*matP;
	Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	Device->SetTexture(0, text->texturePtr);
	Device->SetTransform(D3DTS_WORLD, &matW);
}

void RenderManager::UIRender(Texture * text, Vec2 Pos, Vec2 Size, float rot, D3DCOLOR color)
{
	D3DXMATRIXA16 mat;
	D3DXMatrixTransformation2D(&mat, nullptr, 0, &Size, nullptr, rot, &Pos);
	sprite->SetTransform(&mat);
	sprite->Draw(text->texturePtr, nullptr, &Vec3(text->info.Width/2,text->info.Height/2,0), nullptr, color);

}

void RenderManager::Begin()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void RenderManager::End()
{
	sprite->End();
}

void RenderManager::ResetDevice()
{
	sprite->OnResetDevice();
}

void RenderManager::LostDevice()
{
	sprite->OnLostDevice();
}
