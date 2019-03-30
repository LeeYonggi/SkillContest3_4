#include "DXUT.h"
#include "LoadScene.h"


LoadScene::LoadScene()
{
	loading = thread([&]() { Loading(); });
}


LoadScene::~LoadScene()
{
}

void LoadScene::Init()
{
}

void LoadScene::Loading()
{
	//Background
	MESHMANAGER->AddMesh("Background", L"./Resource/map/map.obj");

	//Player
	MESHMANAGER->AddMeshAnime("Player_Idle", L"./Resource/Player/player_idle/%d.obj", 0, ANIMEFRAME);
	MESHMANAGER->AddMeshAnime("Player_Move", L"./Resource/Player/player_move/%d.obj", 0, ANIMEFRAME);
	
	isEndLoading = true;
}

void LoadScene::Update()
{
	if (isEndLoading)
	{
		if (loading.joinable())
			loading.join();
		SCENEMANAGER->AddScene(new IngameScene());
	}
}

void LoadScene::Render()
{

}

void LoadScene::Release()
{

}
