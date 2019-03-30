#include "DXUT.h"
#include "MainProc.h"


MainProc::MainProc()
{
}


MainProc::~MainProc()
{
}

void MainProc::Init()
{
	SCENEMANAGER->AddScene(new LoadScene);
}

void MainProc::Update()
{
	OBJECTMANAGER->Update();
	SCENEMANAGER->Update();
	INPUTMANAGER->Update();
}

void MainProc::Render()
{
	OBJECTMANAGER->Render();
	SCENEMANAGER->Render();
}

void MainProc::Release()
{
	MeshManager::ReleaseInstance();
	ImageManager::ReleaseInstance();
	ObjectManager::ReleaseInstance();
	SceneManager::ReleaseInstance();
	CameraManager::ReleaseInstance();
}
