#pragma once
#include "Object.h"

enum BULLET_STATE
{
	BULLET_120MM,
	BULLET_88MM,
	BULLET_ENEMY
};

enum BULLET_FUNCSTATE
{
	BULLET_INIT,
	BULLET_UPDATE,
	BULLET_RENDER,
	BULLET_RELEASE
};
class Bullet :
	public Object
{
	using BulletFunc = void(Bullet::*)(BULLET_FUNCSTATE);
public:
	Bullet(Vector3 _pos, Vector3 _moveVector, BULLET_STATE bulletState, float _gravity, float _velocity);
	virtual ~Bullet();

private:
	BULLET_STATE state;
	BulletFunc bulletFunc[BULLET_ENEMY + 1];
	float gravity;
	float velocity;
	float speed = 1.0f;
public:
	int damage = 100;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:
	void Bullet120MM(BULLET_FUNCSTATE funcState);
	void Bullet88MM(BULLET_FUNCSTATE funcState);
	void BulletEnemy(BULLET_FUNCSTATE funcState);
};

