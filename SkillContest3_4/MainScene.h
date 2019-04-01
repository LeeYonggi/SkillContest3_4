#pragma once
#include "Scene.h"
class MainScene :
	public Scene
{
public:
	MainScene();
	virtual ~MainScene();

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

};

