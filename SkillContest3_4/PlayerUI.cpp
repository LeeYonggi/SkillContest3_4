#include "DXUT.h"
#include "PlayerUI.h"

#include "Player.h"


PlayerUI::PlayerUI(Player *_player)
{
	player = _player;
}


PlayerUI::~PlayerUI()
{
}

void PlayerUI::Init()
{
	texture = IMAGEMANAGER->AddTexture(L"MainGameUI", L"./Resource/ui/MainGameUI.png");

}

void PlayerUI::Update()
{
}

void PlayerUI::Render()
{
	IMAGEMANAGER->DrawTexture(texture, {640, 360});
	for (int i = 0; i < 6; i++)
		IMAGEMANAGER->DrawFont(to_string(player->itemCount[i]), {58 + i * 110.0f, 660}, 50);
}

void PlayerUI::Release()
{
}
