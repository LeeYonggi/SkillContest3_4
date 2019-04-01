#include "DXUT.h"
#include "AirEnemy1.h"


AirEnemy1::AirEnemy1(Player *player, Vector3 _pos)
	: Enemy(player, _pos)
{
}


AirEnemy1::~AirEnemy1()
{
}

void AirEnemy1::Init()
{
	mesh = MESHMANAGER->AddMesh("Enemy1", L"./Resource/Enemy/enemy/enemy_1.obj");
	
	enemyFunc[ENEMY_IDLE] = &Enemy::EnemyIdle;
	enemyFunc[ENEMY_MOVE] = &AirEnemy1::AirEnemyMove;
	enemyFunc[ENEMY_ATTACK] = &AirEnemy1::AirEnemyAttack;
	enemyFunc[ENEMY_DIE] = &AirEnemy1::AirEnemyDie;
}

void AirEnemy1::Update()
{
	(this->*enemyFunc[state])();
	EnemyAttacked();
}

void AirEnemy1::Render()
{
	Matrix mat;
	D3DXMatrixRotationY(&mat, D3DXToRadian(-90));
	if(isAttacked)
		MESHMANAGER->DrawMesh(mesh, pos, matR * mat, scale, D3DXCOLOR(1, 0, 0, 1));
	else
		MESHMANAGER->DrawMesh(mesh, pos, matR * mat, scale);
}

void AirEnemy1::Release()
{
}