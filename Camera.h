#pragma once
#include "singleton.h"
class Camera : public singleton<Camera>
{
public:
	Camera();
	~Camera();
public:
	void CamRender();
	void CamReset();
	void CamPosSet(Vec3 Pos,Vec3 Look,Vec3 At);
	Vec3 Pos, Look, At;

};

#define CAMERA Camera::GetInstance()