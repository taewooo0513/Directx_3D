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
	//LOADER->AddMesh(pd3dDevice,"Sex",L"Resource\\(0.obj");

	text = LOADER->AddImage("Title","./Resource/Title.png");
	//mesh = LOADER->AddMesh(pd3dDevice, "Sex", L"Resource\\(0.obj");
}

void Main::Init()
{
	CAMERA->CamReset();
}

void Main::Render()
{
	RENDER->Render2D(text,Vec2(0,0),Vec2(1,1),0);
	//RENDER->Render3D(mesh,Vec3(0,0,-10),Vec3(0.1,0.1,0.1),Vec3(0,3.14,0));
	CAMERA->CamRender();
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
