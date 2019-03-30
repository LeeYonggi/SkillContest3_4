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

	mainCamera->isActive = false;
	Vector3 eye = mainCamera->eye;
	mainCamera = iter->second;
	mainCamera->eye = eye;
	mainCamera->isActive = true;

	return mainCamera;
}
