#include "DXUT.h"
#include "LoadScene.h"

#include "MainScene.h"

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

	//Enemy
	MESHMANAGER->AddMesh("Enemy1", L"./Resource/Enemy/enemy/enemy_1.obj");
	MESHMANAGER->AddMeshAnime("stone", L"./Resource/Enemy/stone/stone%d.obj", 0, 10);
	MESHMANAGER->AddMesh("Enemy1", L"./Resource/Enemy/enemy2/enemy_2.obj");

	//Effect
	IMAGEMANAGER->AddAnimeTexture(L"dust", L"./Resource/Effect/dust/dust_%d.png", 1, 5);
	IMAGEMANAGER->AddAnimeTexture(L"bombGround", L"./Resource/Effect/bombGround/bomb_2_%d.png", 1, 7);
	MESHMANAGER->AddMesh("Plane", L"./Resource/Effect/Plane/bullet.obj");
	IMAGEMANAGER->AddAnimeTexture(L"bulletDestroy", L"./Resource/Effect/attack_effect/%d.png", 1, 5);
	IMAGEMANAGER->AddAnimeTexture(L"EnemyBomb", L"./Resource/Effect/bomb/bomb_%d.png", 1, 8);
	MESHMANAGER->AddMesh("SpeedUp_Model", L"./Resource/Effect/speed_up_model/speed_up.obj");
	IMAGEMANAGER->AddAnimeTexture(L"nuclear_effect", L"./Resource/nuclear_effect/1%04d.jpg", 0, 100);

	//Item
	MESHMANAGER->AddMesh("doubleJump", L"./Resource/item/double_jump/1.obj");
	MESHMANAGER->AddMesh("speed_up", L"./Resource/item/speed_up/1.obj");
	MESHMANAGER->AddMesh("rage_up", L"./Resource/item/rage_up/1.obj");
	MESHMANAGER->AddMesh("3_direction", L"./Resource/item/3_direction/1.obj");
	MESHMANAGER->AddMesh("homing_missile", L"./Resource/item/homing_missile/1.obj");
	MESHMANAGER->AddMesh("nuclear", L"./Resource/item/nuclear/1.obj");
	
	isEndLoading = true;
}

void LoadScene::Update()
{
	if (isEndLoading)
	{
		if (loading.joinable())
			loading.join();
		SCENEMANAGER->AddScene(new MainScene());
	}
}

void LoadScene::Render()
{

}

void LoadScene::Release()
{

}
