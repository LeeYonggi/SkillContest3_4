#include "DXUT.h"
#include "Bullet.h"



Bullet::Bullet(Vector3 _pos, Vector3 _moveVector, BULLET_STATE bulletState, float _gravity)
{
	pos = _pos;
	moveVector = _moveVector;
	state = bulletState;
	gravity = _gravity;
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	bulletFunc[BULLET_120MM] = &Bullet::Bullet120MM;
	bulletFunc[BULLET_88MM] = &Bullet::Bullet88MM;
	bulletFunc[BULLET_ENEMY] = &Bullet::BulletEnemy;

	(this->*bulletFunc[state])(BULLET_INIT);
}

void Bullet::Update()
{
	(this->*bulletFunc[state])(BULLET_UPDATE);
}

void Bullet::Render()
{
	(this->*bulletFunc[state])(BULLET_RENDER);
}

void Bullet::Release()
{
	(this->*bulletFunc[state])(BULLET_RELEASE);
}

void Bullet::Bullet120MM(BULLET_FUNCSTATE funcState)
{
	Vector3 pastPos = pos;
	Vector3 distance = { 0, 0, 0 };
	switch (funcState)
	{
	case BULLET_INIT:
		speed = 100.0f;
		velocity = 0.7f;
		break;
	case BULLET_UPDATE:
		pos += moveVector * ELTIME * speed;
		velocity -= gravity;
		pos.y += velocity;
		distance = GetTargetVec3(pastPos, pos);
		RotateLerp({ 0, 0, 0 }, distance, &matR);

		break;
	case BULLET_RENDER:

		break;
	case BULLET_RELEASE:
		break;
	default:
		break;
	}
}

void Bullet::Bullet88MM(BULLET_FUNCSTATE funcState)
{
	switch (funcState)
	{
	case BULLET_INIT:
		break;
	case BULLET_UPDATE:
		break;
	case BULLET_RENDER:
		break;
	case BULLET_RELEASE:
		break;
	default:
		break;
	}
}

void Bullet::BulletEnemy(BULLET_FUNCSTATE funcState)
{
	switch (funcState)
	{
	case BULLET_INIT:
		break;
	case BULLET_UPDATE:
		break;
	case BULLET_RENDER:
		break;
	case BULLET_RELEASE:
		break;
	default:
		break;
	}
}
