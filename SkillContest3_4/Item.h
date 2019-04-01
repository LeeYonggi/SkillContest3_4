#pragma once
#include "Object.h"

enum ITEM_STATE
{
	ITEM_JUMP,
	ITEM_SPEEDUP,
	ITEM_LENGTHUP,
	ITEM_THIRD,
	ITEM_TRAKING,
	ITEM_NUCLEAR
};
class Item :
	public Object
{
public:
	Item(ITEM_STATE _state, Vector3 _pos);
	virtual ~Item();

public:
	ITEM_STATE itemState;
public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

