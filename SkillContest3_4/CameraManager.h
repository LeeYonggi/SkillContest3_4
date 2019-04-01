#pragma once
#include "Singleton.h"


class CameraManager :
	public Singleton<CameraManager>
{
public:
	CameraManager();
	virtual ~CameraManager();

public:
	Camera *mainCamera = nullptr;
	map<string, Camera*> m_Camera;

public:
	Camera * SetCamera(string name, Camera *camera);
	Camera *ChangeCamera(string name);
	void ShakeCamera(float time);

};

#define CAMERAMANAGER CameraManager::GetInstance()