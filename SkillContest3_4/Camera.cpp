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
	if (shakeTime > 0)
	{
		eye.x += GetRandomNumber(-30, 30) * 0.03f;
		eye.y += GetRandomNumber(-30, 30) * 0.03f;
		eye.z += GetRandomNumber(-30, 30) * 0.03f;
		shakeTime -= ELTIME;
	}
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

void Camera::CameraShake(float time)
{
	shakeTime = time;
}
