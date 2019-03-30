#include "DXUT.h"
#include "CharacterAttack.h"

#include "Bullet.h"

CharacterAttack::CharacterAttack()
{
}


CharacterAttack::~CharacterAttack()
{
}

void CharacterAttack::AttackUpdate()
{
	if (isAttack)
	{
		frame += ELTIME;
		if (frame >= attackdelay)
		{
			isAttack = false;
			frame = 0;
		}
	}
}

void CharacterAttack::Attack(BULLET_STATE bulletState, OBJ_KINDS kind, Vector3 pos, Vector3 moveVector, float gravity)
{
	if (isAttack == true) return;
	isAttack = true;
	OBJECTMANAGER->AddObject(kind, new Bullet(pos, moveVector, bulletState, gravity));
}
