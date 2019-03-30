#pragma once
#include "Camera.h"

class Player;
class TsCamera :
	public Camera
{
public:
	TsCamera(Player *_player);
	virtual ~TsCamera();

private:
	Player *player;

public:
	virtual void Update() override;
};

