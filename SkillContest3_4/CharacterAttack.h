#pragma once

enum BULLET_STATE;
class CharacterAttack
{
public:
	CharacterAttack();
	virtual ~CharacterAttack();

public:
	bool isAttack = false;
	float frame = 0.0f;
	float attackDelay = 0.0f;

public:
	void AttackUpdate();
	void Attack(BULLET_STATE bulletState, OBJ_KINDS kind, Vector3 pos, Vector3 moveVector, float gravity, float _attackDelay, float velocity);
};

