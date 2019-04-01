#include "DXUT.h"
#include "CameraManager.h"


CameraManager::CameraManager()
{
}


CameraManager::~CameraManager()
{
	m_Camera.clear();
}

Camera * CameraManager::SetCamera(string name, Camera * camera)
{
	auto iter = m_Camera.find(name);
	if (iter != m_Camera.end()) return iter->second;

	m_Camera.insert(make_pair(name, camera));
	camera->isActive = false;

	return camera;
}

Camera * CameraManager::ChangeCamera(string name)
{
	auto iter = m_Camera.find(name);
	if (iter == m_Camera.end()) return nullptr;

	if (mainCamera == iter->second) return nullptr;

	Vector3 eye = { 0, 0, 0};
	Vector3 at = { 0, 0 , 0 };
	if (mainCamera)
	{
		mainCamera->isActive = false;
		eye = mainCamera->eye;
		at = mainCamera->at;
	}
	mainCamera = iter->second;
	mainCamera->eye = eye;
	mainCamera->at = at;
	mainCamera->isActive = true;

	return mainCamera;
}
