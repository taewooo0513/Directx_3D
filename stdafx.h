#pragma once
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <math.h>
#include <random>

#define Device DXUTGetD3D9Device()
using namespace std;
const int WINX = 1920;
const int WINY = 1080;
#define Vec2 D3DXVECTOR2
#define Vec3 D3DXVECTOR3

enum TAG
{
	Begin,
	Player,
	End
};
#include "MeshLoader.h"
#include "LoadManager.h"
#include "SceneManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "Component.h"
#include "Camera.h"