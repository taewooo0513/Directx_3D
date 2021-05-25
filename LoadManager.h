#pragma once
#include "singleton.h"
class CMeshLoader;
class Mesh
{
public:
	ID3DXMesh * mesh;
	vector<Material*> materials;
public:
	Mesh() {}
	~Mesh() {}

};
class Texture
{
public:
	LPD3D10EFFECT Effect;
	LPDIRECT3DTEXTURE9 texturePtr;
	D3DXIMAGE_INFO info;
	Texture(LPDIRECT3DTEXTURE9 texturePtr, D3DXIMAGE_INFO info)
		:texturePtr(texturePtr), info(info)
	{

	}
	~Texture()
	{
		texturePtr->Release(); 
	}
};
class LoadManager : public singleton<LoadManager>
{
public:
	map<string, Mesh*> m_mesh;
	map<string, Texture*>m_text;
	map<string, ID3DXEffect *> m_effect;
	CMeshLoader * loader;
	LoadManager();
	~LoadManager();

public:
	
	Mesh * AddMesh(IDirect3DDevice9 * device, string key, const WCHAR * path);
	Texture * AddImage(string key, const string path);
	void AddShader(string key, const string path);
};

#define LOADER LoadManager::GetInstance()