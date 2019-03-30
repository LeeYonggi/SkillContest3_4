#include "DXUT.h"
#include "Player.h"

#include "Background.h"


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

	scale = { 0.02, 0.02, 0.02 };
	pos = {10, distanceGround, 0};
}

void Player::Update()
{
	isControl = false;
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

}

void Player::PlayerMove()
{
	if (!isControl)
		state = PLAYER_IDLE;

}

void Player::PlayerAttack()
{
}

void Player::PlayerRigidbody()
{
	Vector3 temp = PlayerControl(&isControl);
	velocity -= gravity;
	if (isControl)
	{
		moveVector = temp;
		GetDirectionToPoint();

		pos += moveVector * speed;
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
	if (GetPixelCollision(*point * 10, background->minimap1))
	{
		while (true)
		{
			if (GetPixelCollision(*point * 10, background->minimap1))
				point->y += 0.1f;
			else
			{
				point->y -= 0.1f;
				return true;
			}
		}
	}
	else
	{
		for (int i = 0; i < 30; i++)
		{
			if (GetPixelCollision(*point * 10, background->minimap1))
				break;
			else
				point->y -= 0.1f;
		}
	}
	return false;
}
