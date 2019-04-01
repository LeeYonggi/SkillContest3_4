#pragma once
#include "Singleton.h"

enum STAGE_STATE
{
	STAGE_1,
	STAGE_2	
};
class IngameScene :
	public Scene
{
public:
	IngameScene(STAGE_STATE _stage);
	virtual ~IngameScene();

private:
	STAGE_STATE stage;
public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

