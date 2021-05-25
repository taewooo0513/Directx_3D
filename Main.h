#pragma once
class Main
{
public:
	Main();
	~Main();
public:
	void LoadResource(IDirect3DDevice9* pd3dDevice);
	void Init();
	void Render();
	void Update();
	void Release();
	void ResetDevice();
	void LostDevice();
};

