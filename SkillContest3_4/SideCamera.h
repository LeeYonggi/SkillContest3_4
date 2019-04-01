#pragma once
#include "Camera.h"

class Player;
class SideCamera :
	public Camera
{
public:
	SideCamera(Player *_player);
	virtual ~SideCamera();

private:
	Player *player;

public:
	virtual void Update()	override;
};

