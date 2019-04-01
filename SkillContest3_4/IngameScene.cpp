#include "DXUT.h"
#include "IngameScene.h"

#include "ObjCreator.h"

IngameScene::IngameScene(STAGE_STATE _stage)
{
	stage = _stage;
}


IngameScene::~IngameScene()
{
}

void IngameScene::Init()
{
	OBJECTMANAGER->AddObject(OBJ_CREATOR, new ObjCreator(stage));
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
