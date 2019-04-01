#include "DXUT.h"
#include "Player.h"

#include "Background.h"
#include "Bullet.h"
#include "Particle.h"
#include "Item.h"
#include "UI.h"
#include "Enemy.h"
#include "PlayerUI.h"


Player::Player(Background * _background)
{
	background = _background;
}

Player::~Player()
{
}

void Player::Init()
{
	animeMesh.push_back(MESHMANAGER->AddMeshAnime("Player_Idle", L"./Resource/Player/player_idle/%d.obj", 0, ANIMEFRAME));
	animeMesh.push_back(MESHMANAGER->AddMeshAnime("Player_Move", L"./Resource/Player/player_move/%d.obj", 0, ANIMEFRAME));
	animeMesh.push_back(MESHMANAGER->AddMeshAnime("Player_Idle", L"./Resource/Player/player_idle/%d.obj", 0, ANIMEFRAME));

	playerFunc[PLAYER_IDLE] = &Player::PlayerIdle;
	playerFunc[PLAYER_MOVE] = &Player::PlayerMove;
	playerFunc[PLAYER_ATTACK] = &Player::PlayerAttack;
	vector<Texture*> temp = IMAGEMANAGER->AddAnimeTexture(L"dust", L"./Resource/Effect/dust/dust_%d.png", 1, 5);
	vParticle.push_back(OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_EFFECT, new Particle(temp)));
	vParticle[0]->isActive = false; 
	for(int i = 0; i < 3; i++)
		vAttack.push_back(CharacterAttack());

	vector<Texture*> tempTexture = IMAGEMANAGER->AddAnimeTexture(L"speedUp", L"./Resource/Effect/speed_up/%d.png", 1, 4);
	speedUpUI = OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_BACKUI, new UI(tempTexture, {640, 360}, 12, true, true));
	speedUpUI->isActive = false;
	scale = { 0.02, 0.02, 0.02 };
	pos = {10, distanceGround, 0};
	radius = 2.0f;

	OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_UI, new PlayerUI(this));

	memset(itemCount, 0, sizeof(itemCount));

}

void Player::Update()
{
	isControl = false;
	if (INPUTMANAGER->KeyDown(VK_SPACE))
		PlayerJump();
	PlayerRigidbody();
	PlayerAttacked();
	ItemCollision();
	ItemPlay();
	(this->*playerFunc[state])();

	RotateLerp({ 0, 0, 0 }, moveVector, &matR);

	frame += ELTIME;
}

void Player::Render()
{
	int count = int(frame * 15) % animeMesh[state].size();
	MESHMANAGER->DrawMesh(animeMesh[state][count], pos, matR, scale);
}

void Player::Release()
{

}

Vector3 Player::PlayerControl(bool *isControl)
{
	Vector3 temp = { 0, 0, 0 };
	if (INPUTMANAGER->KeyPress(VK_LEFT))
	{
		temp += { -1, 0, 0 };
		*isControl = true;
	}
	if (INPUTMANAGER->KeyPress(VK_RIGHT))
	{
		temp += { 1, 0, 0 };
		*isControl = true;
	}
	if (INPUTMANAGER->KeyPress(VK_UP))
	{
		temp += { 0, 0, 1 };
		*isControl = true;
	}
	if (INPUTMANAGER->KeyPress(VK_DOWN))
	{
		temp += { 0, 0, -1 };
		*isControl = true;
	}

	return temp;
}

void Player::PlayerIdle()
{
	if (isControl)
		state = PLAYER_MOVE;
	if (IsPlayerAttack())
		state = PLAYER_ATTACK;
}

void Player::PlayerMove()
{
	if (!isControl)
		state = PLAYER_IDLE;
	if (IsPlayerAttack())
		state = PLAYER_ATTACK;
	vParticle[0]->isActive = true;
	float pScale = GetRandomNumber(30, 100);
	vParticle[0]->ParticleInit({ pos.x, pos.y - distanceGround + 1.0f, pos.z }, pScale * 0.001f, -moveVector, false, 0.05f, 0.6f);
	pos += moveVector * speed;
}

void Player::PlayerAttack()
{
	for(int i = 0; i < 3; i++)
		vAttack[i].AttackUpdate();
	if(vAttack[0].isAttack == false)
		state = PLAYER_IDLE;
}

void Player::PlayerRigidbody()
{
	Vector3 temp = PlayerControl(&isControl);
	velocity -= gravity;
	if (isControl)
	{
		moveVector = temp;
		GetDirectionToPoint();
	}
	Vector2 tempSide, temptop;
	tempSide.x = pos.x;
	tempSide.y = pos.y - distanceGround;
	temptop.x = pos.x;
	temptop.y = pos.z;
	if (IsPixelCollision(&tempSide) && GetPixelCollision(temptop, background->minimap2))
	{
		velocity = 0;
		pos.y = tempSide.y + distanceGround;
		if (isJump)
		{
			isJump = false;
			jumpCount++;
		}
	}
	pos.y += velocity;
}

void Player::GetDirectionToPoint()
{
	backPoint.x = -moveVector.x * 3 + pos.x;
	backPoint.y = moveVector.y - distanceGround + pos.y;
	frontPoint.x = moveVector.x * 3 + pos.x;
	frontPoint.y = moveVector.y - distanceGround + pos.y;

	IsPixelCollision(&backPoint);
	IsPixelCollision(&frontPoint);

	Vector2 temp = frontPoint - backPoint;
	D3DXVec2Normalize(&temp, &temp);

	moveVector.x = temp.x;
	moveVector.y = temp.y;
}

bool Player::IsPixelCollision(Vector2 * point)
{
	if (GetPixelCollision(*point * 5, background->minimap1))
	{
		while (true)
		{
			if (GetPixelCollision(*point * 5, background->minimap1))
				point->y += 0.2f;
			else
			{
				point->y -= 0.2f;
				return true;
			}
		}
	}
	else
	{
		for (int i = 0; i < 30; i++)
		{
			if (GetPixelCollision(*point * 5, background->minimap1))
				break;
			else
				point->y -= 0.2f;
		}
	}
	return false;
}

void Player::PlayerJump()
{
	if (jumpCount < 1) return;
	velocity = 0.8f;
	pos.y += 0.2f;
	isJump = true;
	jumpCount -= 1;
}

bool Player::IsPlayerAttack()
{
	if (INPUTMANAGER->KeyDown('Q'))
	{
		if (trakingFrame > frame)
		{
			auto iter = OBJECTMANAGER->GetObjectList(OBJ_KINDS::OBJ_ENEMY);
			auto _iter = iter->begin();
			if (_iter != iter->end())
			{
				Enemy *targetEnemy = (Enemy*)(*iter->begin());
				Vector3 tempVector = GetTargetVec3(pos, targetEnemy->pos);
				vAttack[0].Attack(BULLET_STATE::BULLET_120MM, OBJ_KINDS::OBJ_PBULLET, pos, tempVector, 0, 0.6f, 0.0f);
			}
		}
		if (thirdFrame > frame)
		{
			vAttack[0].Attack(BULLET_STATE::BULLET_120MM, OBJ_KINDS::OBJ_PBULLET, pos, moveVector, GRAVITY_SCALE + 0.06f, 0.6f, 0.9f);
			vAttack[1].Attack(BULLET_STATE::BULLET_120MM, OBJ_KINDS::OBJ_PBULLET, pos, moveVector, GRAVITY_SCALE + 0.06f, 0.6f, 1.3f);
			vAttack[2].Attack(BULLET_STATE::BULLET_120MM, OBJ_KINDS::OBJ_PBULLET, pos, moveVector, GRAVITY_SCALE + 0.06f, 0.6f, 1.7f);
		}
		{
			if (lengthFrame < frame)
				vAttack[0].Attack(BULLET_STATE::BULLET_120MM, OBJ_KINDS::OBJ_PBULLET, pos, moveVector, GRAVITY_SCALE + 0.06f, 0.6f, 0.9f);
			else
				vAttack[0].Attack(BULLET_STATE::BULLET_120MM, OBJ_KINDS::OBJ_PBULLET, pos, moveVector, GRAVITY_SCALE + 0.03f, 0.6f, 0.9f);
		}
		return true;
	}
	return false;
}

void Player::PlayerAttacked()
{
	auto iter = OBJECTMANAGER->GetObjectList(OBJ_KINDS::OBJ_EBULLET);
	for (auto bullet = iter->begin(); bullet != iter->end(); iter++)
	{
		if (GetCircleCollision(pos, (*bullet)->pos, radius, (*bullet)->radius))
		{
			(*bullet)->isDestroy = true;
			hp -= 1;
		}
	}
}

void Player::ItemCollision()
{
	auto iter = OBJECTMANAGER->GetObjectList(OBJ_KINDS::OBJ_ITEM);
	for (auto item = iter->begin(); item != iter->end(); item++)
	{
		if (GetCircleCollision(pos, (*item)->pos, radius, (*item)->radius))
		{
			itemCount[((Item*)(*item))->itemState] += 1;
			(*item)->isDestroy = true;
		}
	}
}

void Player::ItemPlay()
{
	if (INPUTMANAGER->KeyDown('1') && itemCount[ITEM_JUMP] > 0)
	{
		jumpCount++;
		itemCount[ITEM_JUMP]--;
	}
	if (INPUTMANAGER->KeyDown('2') && itemCount[ITEM_SPEEDUP] > 0)
	{
		speedUpUI->isActive = true;
		speedUpFrame = frame + 3.0f;
		speed = speed * 1.5f;
		itemCount[ITEM_SPEEDUP]--;
	}
	if (INPUTMANAGER->KeyDown('3') && itemCount[ITEM_LENGTHUP] > 0)
	{
		lengthFrame = frame + 10.0f;
		itemCount[ITEM_LENGTHUP]--;
	}
	if (INPUTMANAGER->KeyDown('4') && itemCount[ITEM_THIRD] > 0)
	{
		thirdFrame = frame + 10.0f;
		itemCount[ITEM_THIRD]--;
	}
	if (INPUTMANAGER->KeyDown('5') && itemCount[ITEM_TRAKING] > 0)
	{
		trakingFrame = frame + 10.0f;
		itemCount[ITEM_TRAKING]--;
	}
	if (INPUTMANAGER->KeyDown('6') && itemCount[ITEM_NUCLEAR] > 0)
	{

		itemCount[ITEM_NUCLEAR]--;
	}
	if (frame > speedUpFrame)
	{
		speedUpUI->isActive = false;
		speed = 0.4f;
	}
}
