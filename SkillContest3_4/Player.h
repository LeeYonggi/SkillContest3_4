#pragma once
#include "Object.h"

enum PLAYER_STATE
{
	PLAYER_IDLE,
	PLAYER_MOVE,
	PLAYER_ATTACK
};
class Background;
class Player :
	public Object
{
	using PlayerFunc = void(Player::*)(void);
public:
	Player(Background *_background);
	virtual ~Player();

private:
	PLAYER_STATE state = PLAYER_IDLE;
	PlayerFunc playerFunc[PLAYER_ATTACK + 1];
	Vector2 backPoint = { 0.0f, 0.0f }, frontPoint = { 0, 0 };
	Background *background;
	float velocity = 0.0f;
	float gravity = BASIC_GRAVITY;
	bool isControl;
	float distanceGround = 5.2f;
	float speed = 0.3f;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:
	Vector3 PlayerControl(bool *isControl);
	void PlayerIdle();
	void PlayerMove();
	void PlayerAttack();
	void PlayerRigidbody();
	void GetDirectionToPoint();
	bool IsPixelCollision(Vector2 *point);
};

