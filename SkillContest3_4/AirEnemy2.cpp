#include "DXUT.h"
#include "AirEnemy2.h"

#include "Player.h"

AirEnemy2::AirEnemy2(Player *player, Vector3 _pos)
	: Enemy(player, _pos)
{
}


AirEnemy2::~AirEnemy2()
{
}

void AirEnemy2::Init()
{
	mesh = MESHMANAGER->AddMesh("Enemy2", L"./Resource/Enemy/enemy2/enemy_2.obj");

	enemyFunc[ENEMY_IDLE] = &Enemy::EnemyIdle;
	enemyFunc[ENEMY_MOVE] = &Enemy::AirEnemyMove;
	enemyFunc[ENEMY_ATTACK] = &Enemy::AirEnemyAttack;
	enemyFunc[ENEMY_DIE] = &Enemy::AirEnemyDie;

	scale = {0.06, 0.06, 0.06};
	hp = 700;
}

void AirEnemy2::Update()
{
	(this->*enemyFunc[state])();
	EnemyAttacked();
}

void AirEnemy2::Render()
{
	Matrix mat;
	D3DXMatrixRotationY(&mat, D3DXToRadian(-90));
	if (isAttacked)
		MESHMANAGER->DrawMesh(mesh, pos, matR * mat, scale, D3DXCOLOR(1, 0, 0, 1));
	else
		MESHMANAGER->DrawMesh(mesh, pos, matR * mat, scale);
}

void AirEnemy2::Release()
{
}
