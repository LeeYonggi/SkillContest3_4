#include "DXUT.h"
#include "Rock.h"

#include "Player.h"
#include "Particle.h"
#include "Item.h"

Rock::Rock(Player *player, Vector3 _pos)
	: Enemy(player, _pos)
{
}


Rock::~Rock()
{
}

void Rock::Init()
{
	animeMesh.push_back(MESHMANAGER->AddMeshAnime("stone", L"./Resource/Enemy/stone/stone%d.obj", 0, 10));
	scale = { 0.4, 0.4, 0.4 };
	pos.y -= 4;
	radius = 15.0f;
}

void Rock::Update()
{
	if (!IsInScreen()) return;

	EnemyAttacked();

	if (hp < 1)
	{
		vParticle[0]->isActive = true;
		Vector3 temp = { 0, 0, 0 };
		temp.x = GetRandomNumber(-3, 3);
		temp.y = GetRandomNumber(-3, 3);
		vParticle[0]->ParticleInit(pos + temp, 0.5, { 0, 0, 0 }, false, 0.3, 0.6f);
		frame += ELTIME;
		if (frame * 12 >= animeMesh[0].size())
		{
			isDestroy = true;
			isActive = false;
			int itemState = GetRandomNumber(0, 5);
			OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_ITEM, new Item((ITEM_STATE)itemState, pos));
		}
	}
}

void Rock::Render()
{
	int count = int(frame * 12) % animeMesh[0].size();
	MESHMANAGER->DrawMesh(animeMesh[0][count], pos, matR, scale);
}

void Rock::Release()
{
}
