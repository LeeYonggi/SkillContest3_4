#pragma once
#include "Object.h"
class Effect :
	public Object
{
public:
	Effect(vector<Texture*> vTexture, Vector3 _pos, float _scale, Vector3 _moveVector, float _isLoop, float _endTime);
	virtual ~Effect();

private:
	bool isLoop = false;
	float endTime = 0.0f;


public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:

};

