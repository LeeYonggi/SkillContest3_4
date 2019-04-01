#include "DXUT.h"
#include "MainScene.h"

#include "UI.h"
#include "IngameScene.h"

MainScene::MainScene()
{
}


MainScene::~MainScene()
{
}

void MainScene::Init()
{
	Texture *tex1 = IMAGEMANAGER->AddTexture(L"start_no_click", L"./Resource/ui/start_no_click.png");
	Texture *tex2 = IMAGEMANAGER->AddTexture(L"start_click", L"./Resource/ui/start_click.png");
	OBJECTMANAGER->AddObject(OBJ_UI, new UI(tex1, tex2, { 640, 350 }, { 403, 147 }, []() {SCENEMANAGER->AddScene(new IngameScene(STAGE_1)); }));

	tex1 = IMAGEMANAGER->AddTexture(L"info_no_click", L"./Resource/ui/info_no_click.png");
	tex2 = IMAGEMANAGER->AddTexture(L"info_click", L"./Resource/ui/info_click.png");
	OBJECTMANAGER->AddObject(OBJ_UI, new UI(tex1, tex2, { 640, 500 }, { 403, 147 }, []() { }));
}

void MainScene::Update()
{

}

void MainScene::Render()
{
}

void MainScene::Release()
{
}
