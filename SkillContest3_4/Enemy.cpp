#include "DXUT.h"
#include "Enemy.h"

#include "Player.h"
#include "Bullet.h"
#include "Particle.h"
#include "Background.h"
#include "Effect.h"


Enemy::Enemy(Player * _player, Vector3 _pos)
{
	player = _player;
	radius = 5.0f;
	pos = _pos;
	scale = { 0.04, 0.04, 0.04 };
	vector<Texture*> temp = IMAGEMANAGER->AddAnimeTexture(L"EnemyBomb", L"./Resource/Effect/bomb/bomb_%d.png", 1, 8);
	vParticle.push_back(OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_EFFECT, new Particle(temp)));
	vParticle[0]->isActive = false;
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
}

void Enemy::Update()
{

}

void Enemy::Render()
{
}

void Enemy::Release()
{
}

void Enemy::AirEnemyMove()
{
	moveVector = GetTargetVec3(pos, { player->pos.x, player->pos.y + 9, player->pos.z });
	velocity += moveVector;
	
	velocity.x = max(min(velocity.x, 20), -20);
	velocity.y = max(min(velocity.y, 3), -3);
	velocity.z = max(min(velocity.z, 20), -20);
	RotateLerp({0, 0, 0}, moveVector, &matR);
	pos += velocity * ELTIME;

	if (GetCircleCollision(pos, player->pos, 20, 1))
		state = ENEMY_ATTACK;
}

bool Enemy::EnemyAttacked()
{
	if (hp < 1)
	{
		state = ENEMY_DIE;
		return true;
	}
	auto iter = OBJECTMANAGER->GetObjectList(OBJ_KINDS::OBJ_PBULLET);
	for (auto bullet = iter->begin(); bullet != iter->end(); bullet++)
	{
		if ((*bullet)->GetCircleCollision(pos, (*bullet)->pos, radius, (*bullet)->radius))
		{
			hp -= ((Bullet*)(*bullet))->damage;
			(*bullet)->isDestroy = true;
			isAttacked = true;
			attackedTime = 0.2f;
		}
	}
	if (GetCircleCollision(player->pos, pos, player->radius, radius))
	{
		player->hp -= 1;
		hp = 0;
	}
	if (attackedTime < 0)
		isAttacked = false;
	attackedTime -= ELTIME;

	return false;
}

void Enemy::AirEnemyAttack()
{
	velocity.x = Lerp(velocity.x, 0.0f, 0.1f);
	velocity.z = Lerp(velocity.z, 0.0f, 0.1f);
	moveVector = GetTargetVec3(pos, { player->pos.x, player->pos.y + 9, player->pos.z });
	velocity.y += moveVector.y;
	velocity.y = max(min(velocity.y, 3), -3);

	RotateLerp({ 0, 0, 0 }, moveVector, &matR);

	pos += velocity * ELTIME;
	pos.z = Lerp(pos.z, player->pos.z, 0.03f);

	if (!GetCircleCollision(pos, player->pos, 20, 1))
		state = ENEMY_MOVE;
}

void Enemy::EnemyIdle()
{
	if (IsInScreen())
		state = ENEMY_MOVE;
}

void Enemy::AirEnemyDie()
{
	velocity.y -= 1.f;

	vParticle[0]->isActive = true;
	float rScale = GetRandomNumber(20, 40);
	vParticle[0]->ParticleInit(pos, rScale * 0.01, { 0, 0, 0 }, false, 0.4f, 0.6f);
	RotateLerp({ 0, 0, 0 }, velocity, &matR);

	auto iter = OBJECTMANAGER->GetObjectList(OBJ_BACKGROUND);
	if (GetPixelCollision(Vector2(pos.x, pos.y) * 5, ((Background*)*iter->begin())->minimap1) ||
		pos.y < -400)
	{
		vector<Texture*> temp = IMAGEMANAGER->AddAnimeTexture(L"EnemyBomb", L"./Resource/Effect/bomb/bomb_%d.png", 1, 8);
		OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_ENEMY, new Effect(temp, pos, 0.4f, {0, 0, 0}, false, 0.6f));
		isDestroy = true;
	}
	pos += velocity * ELTIME;
}

bool Enemy::IsInScreen()
{
	return (CAMERAMANAGER->mainCamera->eye.x - 40 < pos.x && CAMERAMANAGER->mainCamera->eye.x + 40 > pos.x);
}
