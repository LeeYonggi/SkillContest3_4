#pragma once
#include "UI.h"

class Player;
class PlayerUI :
	public UI
{
public:
	PlayerUI(Player *_player);
	virtual ~PlayerUI();

private:
	Player *player;

public:

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

