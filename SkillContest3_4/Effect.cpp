#include "DXUT.h"
#include "Effect.h"



Effect::Effect(vector<Texture*> vTexture, Vector3 _pos, float _scale, Vector3 _moveVector, float _isLoop, float _endTime)
{
	pos = _pos;
	scale = { _scale, _scale, _scale };
	moveVector = _moveVector;
	isLoop = _isLoop;
	endTime = _endTime;
	animeTexture.push_back(vTexture);
}

Effect::~Effect()
{
}

void Effect::Init()
{

}

void Effect::Update()
{
	frame += ELTIME;
	if (isLoop)
	{
		if (frame >= endTime)
		{
			isDestroy = true;
			isActive = false;
		}
	}
	else
	{
		if (frame * 12 >= animeTexture[0].size())
		{
			isDestroy = true;
			isActive = false;
		}
	}
}

void Effect::Render()
{
	int count = int(frame * 12) % animeTexture[0].size();
	matR = GetBillboard(pos, CAMERAMANAGER->mainCamera->eye);
	MESHMANAGER->DrawEffect();
}

void Effect::Release()
{
}
