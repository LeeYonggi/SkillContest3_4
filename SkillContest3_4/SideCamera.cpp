#include "DXUT.h"
#include "SideCamera.h"

#include "Player.h"

SideCamera::SideCamera(Player *_player)
{
	player = _player;
}


SideCamera::~SideCamera()
{
}


void SideCamera::Update()
{
	Camera::Update();
	Vector3 temp = player->pos;
	at = player->pos;
	temp.z -= 40;
	eye = Lerp(eye, temp, 0.1f);
}
