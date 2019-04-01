#pragma once
#include "Object.h"
class Camera :
	public Object
{
public:
	Camera();
	virtual ~Camera();

public:
	Vector3 at = { 0, 0, 0 };
	Vector3 eye = { 0, 0, 0 };
	Vector3 up = {0, 1, 0};
	float shakeTime = 0.0;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void CameraShake(float time);
};

