#pragma once
#include "Object.h"
#include "CharacterAttack.h"

enum PLAYER_STATE;
class Player;
class PlayerArm :
	public Object
{
	using PlayerArmFunc = void(PlayerArm::*)(void);
public:
	PlayerArm(Player *_player);
	virtual ~PlayerArm();

private:
	Player * player;
	PLAYER_STATE state;
	PlayerArmFunc playerArmFunc[3];
	vector<CharacterAttack> vAttack;
	float attackDistance = 0.0f;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:
	void PlayerArmIdle();
	void PlayerArmMove();
	void PlayerArmAttack();
};

