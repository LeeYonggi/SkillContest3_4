#include "DXUT.h"
#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::Init()
{
}

void Camera::Update()
{
}

void Camera::Render()
{
	Matrix matView, proj;
	D3DXMatrixLookAtLH(&matView, &eye, &at, &up);
	
	DEVICE->SetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixPerspectiveFovLH(&proj, D3DXToRadian(60), (float)SCREEN_X / (float)SCREEN_Y, 1, 1000000.0f);
	DEVICE->SetTransform(D3DTS_PROJECTION, &proj);
}

void Camera::Release()
{
}
