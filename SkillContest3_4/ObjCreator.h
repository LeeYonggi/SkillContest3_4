#pragma once
#include "Object.h"

class Player;
class Background;
class ObjCreator :
	public Object
{
public:
	ObjCreator(STAGE_STATE _stage);
	virtual ~ObjCreator();

private:
	STAGE_STATE stage;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:
	void MakeRock1(Player *player, Background *back);
};

