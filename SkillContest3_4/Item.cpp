#include "DXUT.h"
#include "Item.h"

#include "Effect.h"

Item::Item(ITEM_STATE _state, Vector3 _pos)
{
	itemState = _state;
	pos = _pos;
	pos.y += 5.0f;
	scale = { 0.05, 0.05, 0.05 };
	radius = 3;
}


Item::~Item()
{
}

void Item::Init()
{
	switch (itemState)
	{
	case ITEM_JUMP:
		mesh = MESHMANAGER->AddMesh("doubleJump", L"./Resource/item/double_jump/1.obj");
		break;
	case ITEM_SPEEDUP:
		mesh = MESHMANAGER->AddMesh("speed_up", L"./Resource/item/speed_up/1.obj");
		break;
	case ITEM_LENGTHUP:
		mesh = MESHMANAGER->AddMesh("rage_up", L"./Resource/item/rage_up/1.obj");
		break;
	case ITEM_THIRD:
		mesh = MESHMANAGER->AddMesh("3_direction", L"./Resource/item/3_direction/1.obj");
		break;
	case ITEM_TRAKING:
		mesh = MESHMANAGER->AddMesh("homing_missile", L"./Resource/item/homing_missile/1.obj");
		break;
	case ITEM_NUCLEAR:
		mesh = MESHMANAGER->AddMesh("nuclear", L"./Resource/item/nuclear/1.obj");
		break;
	default:
		break;
	}
}

void Item::Update()
{
	pos.y += sin(frame * 5) * 10 * ELTIME;

	frame += ELTIME;
}

void Item::Render()
{
	MESHMANAGER->DrawMesh(mesh, pos, matR, scale);
}

void Item::Release()
{
	vector<Texture*> particleTexture = IMAGEMANAGER->AddAnimeTexture(L"bulletDestroy", L"./Resource/Effect/attack_effect/%d.png", 1, 5);
	OBJECTMANAGER->AddObject(OBJ_EFFECT, new Effect(particleTexture, pos, 0.5f, { 0, 0, 0 }, false, 0.6f));
}
