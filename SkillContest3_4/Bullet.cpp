#include "DXUT.h"
#include "Bullet.h"

#include "Particle.h"
#include "Background.h"
#include "Effect.h"


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

	auto iter = OBJECTMANAGER->GetObjectList(OBJ_KINDS::OBJ_BACKGROUND);
	Vector2 temp = Vector2(pos.x, pos.y);
	if (GetPixelCollision(temp * 5.0f, ((Background*)*iter->begin())->minimap1))
	{
		isDestroy = true;
	}
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
	vector<Texture*> particleTexture;
	switch (funcState)
	{
	case BULLET_INIT:
		speed = 70.0f;
		velocity = 0.9f;
		mesh = MESHMANAGER->AddMesh("120MM", L"./Resource/Bullet/120MM/skill.obj");
		scale = { 0.1, 0.1, 0.1 };
		particleTexture = IMAGEMANAGER->AddAnimeTexture(L"dust", L"./Resource/Effect/dust/dust_%d.png", 1, 5);
		vParticle.push_back(OBJECTMANAGER->AddObject(OBJ_EFFECT, new Particle(particleTexture)));
		vParticle[0]->isActive = false;
		break;
	case BULLET_UPDATE:
	{
		pos += moveVector * ELTIME * speed;
		velocity -= gravity;
		pos.y += velocity;
		distance = GetTargetVec3(pastPos, pos);
		D3DXMatrixLookAtLH(&matR, &Vector3(0, 0, 0), &distance, &Vector3(0, 1, 0));
		D3DXMatrixTranspose(&matR, &matR);
		float rScale = GetRandomNumber(50, 100);
		vParticle[0]->ParticleInit(pos, rScale * 0.001f, -distance * 30, false, 0.05f, 0.6f);

		vParticle[0]->isActive = true;
	}
		break;
	case BULLET_RENDER:
		MESHMANAGER->DrawMesh(mesh, pos, matR, scale);
		break;
	case BULLET_RELEASE:
		particleTexture = IMAGEMANAGER->AddAnimeTexture(L"bombGround", L"./Resource/Effect/bombGround/bomb_2_%d.png", 1, 7);
		OBJECTMANAGER->AddObject(OBJ_EFFECT, new Effect(particleTexture, pos, 0.3f, { 0, 0, 0 }, false, 0.6f));
		for (int i = 0; i < 360; i += 30)
		{
			Vector3 tempVec3;
			tempVec3.x = sin(D3DXToRadian(i));
			tempVec3.y = cos(D3DXToRadian(i));
			particleTexture = IMAGEMANAGER->AddAnimeTexture(L"dust", L"./Resource/Effect/dust/dust_%d.png", 1, 5);
			float tempScale = GetRandomNumber(50, 100);
			OBJECTMANAGER->AddObject(OBJ_EFFECT, new Effect(particleTexture, pos, tempScale * 0.001, tempVec3 * 10, false, 0.6f));
		}
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
		mesh = MESHMANAGER->AddMesh("Plane", L"./Resource/Effect/Plane/bullet.obj");
		texture = IMAGEMANAGER->AddTexture(L"88MM", L"./Resource/Bullet/88MM/88MM.png");
		speed = 100.0f;
		scale = { 0.02, 0.02, 0.02 };

		break;
	case BULLET_UPDATE:

		pos += moveVector * ELTIME * speed;
		break;
	case BULLET_RENDER:
		matR = GetBillboard(pos, CAMERAMANAGER->mainCamera->eye);
		MESHMANAGER->DrawEffect(mesh, texture, pos, matR, scale);
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
