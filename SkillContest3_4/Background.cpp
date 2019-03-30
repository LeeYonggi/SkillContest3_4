#include "DXUT.h"
#include "Background.h"


Background::Background()
{
}


Background::~Background()
{
}

void Background::Init()
{
	minimap1 = IMAGEMANAGER->AddTexture(L"minimap1", L"./Resource/map/minimap/side.png");
	minimap2 = IMAGEMANAGER->AddTexture(L"minimap2", L"./Resource/map/minimap/top.png");
	mesh = MESHMANAGER->AddMesh("Background", L"./Resource/map/map.obj");
	pos = { 0, 0, -12 };
	scale = { 1, 1, 1 };
}

void Background::Update()
{
}

void Background::Render()
{
	MESHMANAGER->DrawMesh(mesh, pos, matR, scale);
}

void Background::Release()
{
}
