#include "DXUT.h"
#include "Main.h"

Main::Main()
{
}

Main::~Main()
{
}
Texture * text;
Mesh * mesh;
void Main::LoadResource(IDirect3DDevice9 * pd3dDevice)
{
	LOADER->AddMesh(pd3dDevice,"Sex",L"Resource\\(0.obj");

	LOADER->AddShader("Shadow","./Shadow.fx");
	text = LOADER->AddImage("Title","./Resource/Title.png");
	mesh = LOADER->AddMesh(pd3dDevice, "Sex", L"Resource\\(0.obj");
}

void Main::Init()
{
	Pos = Vec3(0, 0, -10);
	CAMERA->CamReset();
}

void Main::Render()
{
	if (DXUTIsKeyDown(VK_LEFT))
	{
		Pos.x -= 0.1;
	}
	if (DXUTIsKeyDown(VK_RIGHT))
	{
		Pos.x += 0.1;
	}
	RENDER->Render2D(text,Vec3(0,0,-50),Vec2(1,1),0);
	RENDER->ShadowRender(mesh, Pos,Vec3(0.1,0.1,0.1),Vec3(0,D3DX_PI,0));
	RENDER->Render3D(mesh, Vec3(-10, 0, -10), Vec3(0.1, 0.1, 0.1), Vec3(0,Pos.x,0));
	RENDER->ShadowRender(mesh, Vec3(-20, 0, -10), Vec3(0.05, 0.05, 0.05), Vec3(0, Pos.x, 0));
	RENDER->ShadowRender(mesh, Vec3(-30, 0, -10), Vec3(0.1, 0.1, 0.1), Vec3(0, 3.14, 0));
	CAMERA->CamRender();

	RENDER->Begin();
	RENDER->End();
}

void Main::Update()
{
}

void Main::Release()
{
	LoadManager::ReleaseInstance();
	RenderManager::ReleaseInstance();
}

void Main::ResetDevice()
{
}

void Main::LostDevice()
{
}
