#include "DXUT.h"
#include "SceneManager.h"


SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}


void SceneManager::AddScene(Scene * scene)
{
	pastScene = scene;
	isSceneChange = true;
}

void SceneManager::Update()
{
	if (isSceneChange)
	{
		if (nowScene)
		{
			SAFE_RELEASE(nowScene);
			SAFE_DELETE(nowScene);
			OBJECTMANAGER->Release();
			OBJECTMANAGER->Init();
		}
		nowScene = pastScene;
		pastScene = nullptr;
		nowScene->Init();
		isSceneChange = false;
	}
	if (nowScene)
		nowScene->Update();
}

void SceneManager::Render()
{
	if (nowScene)
		nowScene->Render();
}

void SceneManager::Release()
{
	SAFE_RELEASE(nowScene);
	SAFE_DELETE(nowScene);
	SAFE_RELEASE(pastScene);
	SAFE_DELETE(pastScene);

}
