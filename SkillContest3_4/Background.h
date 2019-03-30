#pragma once
#include "Object.h"

class Background :
	public Object
{
public:
	Background();
	virtual ~Background();

public:
	Texture *minimap1;
	Texture *minimap2;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

};

