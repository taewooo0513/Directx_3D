#include "DXUT.h"
#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::CamRender()
{
	D3DXMATRIXA16 matProj;
	D3DXMatrixOrthoLH(&matProj, WINX, WINY, 0, 100);
	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(60), 16.f / 9.f, 1.f, 50000.f);
	Device->SetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &Pos, &Look, &At);
	Device->SetTransform(D3DTS_VIEW, &matView);
}

void Camera::CamReset()
{
	Pos = Vec3(0, 0, -10);
	Look = Vec3(0, 0, 10);
	At = Vec3(0, 1, 0);
}

void Camera::CamPosSet(Vec3 Pos, Vec3 Look, Vec3 At)
{
	this->Pos = Pos;
	this->Look = Look;
	this->At = At;
}
