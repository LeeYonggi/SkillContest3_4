#pragma once
#include "Object.h"
#include "CharacterAttack.h"

enum PLAYER_STATE
{
	PLAYER_IDLE,
	PLAYER_MOVE,
	PLAYER_ATTACK
};
class Background;
class UI;
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
	float gravity = GRAVITY_SCALE;
	bool isControl;
	float distanceGround = 5.2f;
	float speed = 0.4f;
	int jumpCount = 1;
	bool isJump = false;
	vector<CharacterAttack> vAttack;

private:
	float lengthFrame = 0.0f;
	UI *speedUpUI = nullptr;
	UI *nuclear = nullptr;
	float speedUpFrame = 0.0f;
	float thirdFrame = 0.0f;
	float trakingFrame = 0.0f;
	bool isNuclear = false;
	CMeshLoader *speedUpModel = nullptr;


public:
	int hp = 1;
	int totalHp = 3;
	int itemCount[6];

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
	void PlayerJump();
	bool IsPlayerAttack();
	void PlayerAttacked();
	void ItemCollision();
	void ItemPlay();
};

