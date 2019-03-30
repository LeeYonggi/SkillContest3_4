#include "DXUT.h"
#include "IngameScene.h"

#include "Player.h"
#include "TsCamera.h"
#include "Background.h"

IngameScene::IngameScene()
{
}


IngameScene::~IngameScene()
{
}

void IngameScene::Init()
{
	Background *background = OBJECTMANAGER->AddObject(OBJ_BACKGROUND, new Background());
	Player *player = OBJECTMANAGER->AddObject(OBJ_PLAYER, new Player(background));
	Camera *camera = OBJECTMANAGER->AddObject(OBJ_CAMERA, new TsCamera(player));
	CAMERAMANAGER->SetCamera("TsCamera", camera);
	CAMERAMANAGER->ChangeCamera("TsCamera");
}

void IngameScene::Update()
{
}

void IngameScene::Render()
{
}

void IngameScene::Release()
{
}
