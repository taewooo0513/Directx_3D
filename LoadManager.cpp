#include "DXUT.h"
#include "LoadManager.h"

LoadManager::LoadManager()
{
	loader = new CMeshLoader;
}

LoadManager::~LoadManager()
{
	SAFE_DELETE(loader);

	for (auto iter : m_mesh)
	{
		iter.second->materials.clear();
		SAFE_DELETE(iter.second);
	}
	m_mesh.clear();

	for (auto iter : m_text)
	{
		iter.second->texturePtr->Release();
		SAFE_DELETE(iter.second);
	}
	m_text.clear();

	for (auto iter : m_effect)
	{
		iter.second->Release();
		SAFE_DELETE(iter.second);
	}
	m_effect.clear();
}

Mesh * LoadManager::AddMesh(IDirect3DDevice9 * device, string key, const WCHAR * path)
{
	auto find = m_mesh.find(key);
	if (find != m_mesh.end())
	{
		return find->second;
	}
	Mesh * mesh = new Mesh;
	if (loader->Create(Device, path) == S_OK)
	{
		m_mesh[key] = mesh;
		m_mesh[key]->mesh = loader->GetMesh();
		for (int i = 0; i < loader->GetNumMaterials(); i++)
		{
			m_mesh[key]->materials.push_back(loader->GetMaterial(i));
		}
		return mesh;
	}
	return nullptr;
}

Texture * LoadManager::AddImage(string key, const string path)
{
	auto find = m_text.find(key);
	if (find != m_text.end())
	{
		return find->second;
	}
	LPDIRECT3DTEXTURE9 textureptr;
	D3DXIMAGE_INFO info;
	if (D3DXCreateTextureFromFileExA(Device, path.c_str(), -2, -2, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, -1, -1, 0, &info, nullptr, &textureptr) == S_OK)
	{
		Texture * text = new Texture(textureptr, info);
		m_text[key] = text;
		return text;
	}
	return nullptr;
}

void LoadManager::AddShader(string key, const string path)
{
	ID3DXEffect * effect;
	LPD3DXBUFFER buf;
	if (D3DXCreateEffectFromFileExA(Device, path.c_str(), 0, 0, 0, D3DXFX_NOT_CLONEABLE, NULL, &effect, &buf) == S_OK)
	{
		m_effect[key] = effect;
	}
		else
		MessageBoxA(DXUTGetHWND(), (LPSTR)buf->GetBufferPointer(), NULL, NULL);

}
