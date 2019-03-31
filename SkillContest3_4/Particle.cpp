#include "DXUT.h"
#include "Particle.h"

#include "Effect.h"

Particle::Particle(vector<Texture*> animeTexture)
{
	this->animeTexture.push_back(animeTexture);
}


Particle::~Particle()
{
}

void Particle::Init()
{

}

void Particle::Update()
{
	if (frame >= fireDelay)
	{
		OBJECTMANAGER->AddObject(OBJ_EFFECT, new Effect(animeTexture[0], pos, scale.x, moveVector, isLoop, endTime));
		frame = 0;
	}
	frame += ELTIME;
}

void Particle::Render()
{
}

void Particle::Release()
{
}

void Particle::ParticleInit(Vector3 _pos, float _scale, Vector3 _moveVector, bool _isLoop, float _fireDelay, float _endTime)
{
	pos = _pos;
	scale.x = _scale;
	moveVector = _moveVector;
	isLoop = _isLoop;
	fireDelay = _fireDelay;
	endTime = _endTime;
}
