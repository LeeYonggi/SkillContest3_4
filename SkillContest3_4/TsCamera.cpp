#include "DXUT.h"
#include "TsCamera.h"

#include "Player.h"

TsCamera::TsCamera(Player *_player)
{
	player = _player;
}


TsCamera::~TsCamera()
{
}

void TsCamera::Update()
{
	Camera::Update();
	Vector3 temp = player->pos;
	at = player->pos;
	temp.y += 10;
	temp.z -= 30;
	eye = Lerp(eye, temp, 0.1f);

}
