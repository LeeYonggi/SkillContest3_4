#include "DXUT.h"
#include "ObjCreator.h"

#include "Player.h"
#include "TsCamera.h"
#include "Background.h"
#include "PlayerArm.h"
#include "AirEnemy1.h"
#include "Rock.h"
#include "SideCamera.h"
#include "AirEnemy2.h"


ObjCreator::ObjCreator(STAGE_STATE _stage)
{
	stage = _stage;
}


ObjCreator::~ObjCreator()
{
}

void ObjCreator::Init()
{
	switch (stage)
	{
	case STAGE_1:
	{
		Background *background = OBJECTMANAGER->AddObject(OBJ_BACKGROUND, new Background());
		Player *player = OBJECTMANAGER->AddObject(OBJ_PLAYER, new Player(background));
		OBJECTMANAGER->AddObject(OBJ_PLAYER, new PlayerArm(player));
		for (int i = 0; i < 35; i++)
		{
			int n = GetRandomNumber(0, 10);
			float tempY = 10.f;
			if (i > 9)
				tempY = -130;
			else
				tempY = 10;
			if (n < 8)
				OBJECTMANAGER->AddObject(OBJ_ENEMY, new AirEnemy1(player, { i * 30.0f, tempY, 0 }));
			else
				OBJECTMANAGER->AddObject(OBJ_ENEMY, new AirEnemy2(player, { i * 30.0f, tempY, 0 }));
		}
		MakeRock1(player, background);
		Camera *camera = OBJECTMANAGER->AddObject(OBJ_CAMERA, new TsCamera(player));
		CAMERAMANAGER->SetCamera("TsCamera", camera);
		camera = OBJECTMANAGER->AddObject(OBJ_CAMERA, new SideCamera(player));
		CAMERAMANAGER->SetCamera("SideCamera", camera);

		CAMERAMANAGER->ChangeCamera("TsCamera");
	}
		break;
	case STAGE_2:

		break;
	default:
		break;
	}
}

void ObjCreator::Update()
{
	switch (stage)
	{
	case STAGE_1:
		if (CAMERAMANAGER->mainCamera->eye.x > 400 && CAMERAMANAGER->mainCamera->eye.x < 860)
		{
			CAMERAMANAGER->ChangeCamera("SideCamera");
		}
		else
		{
			CAMERAMANAGER->ChangeCamera("TsCamera");
		}
		break;
	case STAGE_2:
		break;
	default:
		break;
	}
}

void ObjCreator::Render()
{
}

void ObjCreator::Release()
{
}

void ObjCreator::MakeRock1(Player * player, Background *back)
{
	float sideY = 237;
	float topZ = 125;

	int i = 0;
	int none = 0;
	while(true)
	{
		Vector3 tempPos = { i * 30.0f + 60, 0, 0 };
		tempPos.z = GetRandomNumber(-100, 100);
		if (GetPixelCollision({ tempPos.x, tempPos.z }, back->minimap2))
		{
			if (i > 9)
				tempPos.y = 0 - (384 - sideY);
			OBJECTMANAGER->AddObject(OBJ_ENEMY, new Rock(player, { tempPos.x, tempPos.y, tempPos.z }));
			i++;
			none = 0;
		}
		else
		{
			if (none > 60)
				i++;
			none++;
			continue;
		}
		if (i > 29)
			break;
	}
}
