#pragma once
#include "Object.h"
class Particle :
	public Object
{
public:
	Particle(vector<Texture*> animeMesh);
	virtual ~Particle();

private:
	float fireDelay = 0.0f;
	bool isLoop = false;
	float endTime = 0.0f;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:
	void ParticleInit(Vector3 _pos, float _scale, Vector3 _moveVector, bool _isLoop, float _fireDelay, float _endTime);
};

