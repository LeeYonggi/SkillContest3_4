#pragma once
#include "Object.h"

class Player;
enum ENEMY_STATE
{
	ENEMY_IDLE,	
	ENEMY_MOVE,
	ENEMY_ATTACK,
	ENEMY_DIE
};
class Enemy :
	public Object
{
	using EnemyFunc = void(Enemy::*)(void);
public:
	Enemy(Player *_player, Vector3 _pos);
	virtual ~Enemy();

protected:
	Player *player;
	ENEMY_STATE state = ENEMY_IDLE;
	EnemyFunc enemyFunc[4];
	Vector3 velocity = { 0, 0, 0 };
	bool isAttacked = false;
	float attackedTime = 0.0f;
	
public:
	int hp = 500;
public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:
	void AirEnemyMove();
	bool EnemyAttacked();
	void AirEnemyAttack();
	void EnemyIdle();
	void AirEnemyDie();
	bool IsInScreen(); 
};

