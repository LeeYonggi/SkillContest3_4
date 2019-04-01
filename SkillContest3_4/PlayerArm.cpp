#include "DXUT.h"
#include "PlayerArm.h"

#include "Player.h"
#include "Bullet.h"

PlayerArm::PlayerArm(Player *_player)
{
	player = _player;
}


PlayerArm::~PlayerArm()
{
}

void PlayerArm::Init()
{
	animeMesh.push_back(MESHMANAGER->AddMeshAnime("Player_Arm_Idle", L"./Resource/Player/arm/%d.obj", 0, ANIMEFRAME));
	animeMesh.push_back(MESHMANAGER->AddMeshAnime("Player_Arm_Idle", L"./Resource/Player/arm/%d.obj", 0, ANIMEFRAME));
	animeMesh.push_back(MESHMANAGER->AddMeshAnime("Player_Arm_Attack", L"./Resource/Player/attack/%d.obj", 0, ANIMEFRAME));

	state = PLAYER_IDLE;

	playerArmFunc[PLAYER_IDLE] = &PlayerArm::PlayerArmIdle;
	playerArmFunc[PLAYER_MOVE] = &PlayerArm::PlayerArmMove;
	playerArmFunc[PLAYER_ATTACK] = &PlayerArm::PlayerArmAttack;

	vAttack.push_back(CharacterAttack());
	vAttack.push_back(CharacterAttack());
}

void PlayerArm::Update()
{
	pos = player->pos;
	scale = player->scale;
	if (INPUTMANAGER->KeyDown('A'))
	{
		attackDistance += 0.5f;
		if (attackDistance > 4.0f)
			attackDistance = 0.0f;
		else if (attackDistance > 0.5f)
			attackDistance = 4.0f;
	}
	if (INPUTMANAGER->KeyDown('S'))
	{
		attackDistance -= 0.5f;
		if (attackDistance < 0.0f)
			attackDistance = 4.0f;
		else if (attackDistance < 4.0f && attackDistance > 3.0f)
			attackDistance = 0.5f;
	}
	moveVector = player->moveVector;
	moveVector.y += attackDistance;
	RotateLerp({ 0, 0, 0 }, moveVector, &matR);

	(this->*playerArmFunc[state])();

	frame += ELTIME;
}

void PlayerArm::Render()
{
	int count = int(frame * 15) % animeMesh[state].size();
	MESHMANAGER->DrawMesh(animeMesh[state][count], pos, matR, scale);
}

void PlayerArm::Release()
{
}

void PlayerArm::PlayerArmIdle()
{
	if (INPUTMANAGER->KeyDown('W'))
		state = PLAYER_ATTACK;
}

void PlayerArm::PlayerArmMove()
{
}

void PlayerArm::PlayerArmAttack()
{
	if (INPUTMANAGER->KeyDown('W'))
		state = PLAYER_IDLE;

	for (int i = 0; i < 2; i++)
	{
		Vector3 bMoveVector = { 0, 0, 1 }, startVector = { 0, 0, 1 };
		D3DXVec3TransformCoord(&bMoveVector, &bMoveVector, &matR);
		Matrix mat;
		D3DXMatrixRotationY(&mat, D3DXToRadian(-30 + i * 60));
		mat *= matR;
		D3DXVec3TransformCoord(&startVector, &startVector, &mat);

		vAttack[i].Attack(BULLET_STATE::BULLET_88MM, OBJ_KINDS::OBJ_PBULLET, pos + startVector * 3, bMoveVector, 0, 0.4f, 0);
		vAttack[i].AttackUpdate();

	}
}
