#pragma once
#include "Object.h"
class Particle :
	public Object
{
public:
	Particle();
	virtual ~Particle();

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

