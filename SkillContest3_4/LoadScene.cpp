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
	MESHMANAGER->AddMeshAnime("Player_Arm_Idle", L"./Resource/Player/arm/%d.obj", 0, ANIMEFRAME);
	MESHMANAGER->AddMeshAnime("Player_Arm_Attack", L"./Resource/Player/attack/%d.obj", 0, ANIMEFRAME);

	//Bullet
	MESHMANAGER->AddMesh("120MM", L"./Resource/Bullet/120MM/skill.obj");
	IMAGEMANAGER->AddTexture(L"88MM", L"./Resource/Bullet/88MM/88MM.png");

	//Effect
	IMAGEMANAGER->AddAnimeTexture(L"dust", L"./Resource/Effect/dust/dust_%d.png", 1, 5);
	IMAGEMANAGER->AddAnimeTexture(L"bombGround", L"./Resource/Effect/bombGround/bomb_2_%d.png", 1, 7);
	MESHMANAGER->AddMesh("Plane", L"./Resource/Effect/Plane/bullet.obj");
	
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
