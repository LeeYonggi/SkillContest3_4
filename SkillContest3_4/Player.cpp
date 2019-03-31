#include "DXUT.h"
#include "Player.h"

#include "Background.h"
#include "Bullet.h"


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
	vAttack.push_back(CharacterAttack());

	scale = { 0.02, 0.02, 0.02 };
	pos = {10, distanceGround, 0};
}

void Player::Update()
{
	isControl = false;
	if (INPUTMANAGER->KeyDown(VK_SPACE))
		PlayerJump();
	PlayerRigidbody();
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

	pos += moveVector * speed;
}

void Player::PlayerAttack()
{
	vAttack[0].AttackUpdate();
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
	velocity = 0.6f;
	pos.y += 0.2f;
	isJump = true;
	jumpCount -= 1;
}

bool Player::IsPlayerAttack()
{
	if (INPUTMANAGER->KeyDown('Q'))
	{
		vAttack[0].Attack(BULLET_STATE::BULLET_120MM, OBJ_KINDS::OBJ_PBULLET, pos, moveVector, GRAVITY_SCALE + 0.06f, 0.6f);
		return true;
	}
	return false;
}
