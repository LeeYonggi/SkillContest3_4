#include "DXUT.h"
#include "UI.h"



UI::UI(vector<Texture*> _animeTexture, Vector2 _pos, float _animeSpeed, bool isLoop, bool _isElaps)
{
	isButton = false;
	isElaps = _isElaps;
	animeTexture.push_back(_animeTexture);
	pos.x = _pos.x;
	pos.y = _pos.y;
	animeSpeed = _animeSpeed;
	this->isLoop = isLoop;
	isElaps = _isElaps;
}

UI::UI(Texture * up, Texture * down, Vector2 _pos, Vector2 size)
{
	isButton = true;
	upTex = up;
	downTex = down;
}

UI::~UI()
{
}

void UI::Init()
{

}

void UI::Update()
{
	if (isButton)
	{

	}
	else
	{
		if (isElaps)
		{
			frame += ELTIME;
			if (!isLoop && frame * animeSpeed >= animeTexture[0].size())
			{
				isDestroy = true;
				isActive = false;
			}
		}
		else
		{
			frame += animeSpeed;
			if (!isLoop && frame >= animeTexture[0].size())
			{
				isDestroy = true;
				isActive = false;
			}
		}
	}
}

void UI::Render()
{
	if (isButton)
	{
		if (isDown)
		{
			IMAGEMANAGER->DrawTexture(downTex, { pos.x, pos.y });
		}
		else
		{
			IMAGEMANAGER->DrawTexture(upTex, { pos.x, pos.y });
		}
	}
	else
	{
		if (isElaps)
		{
			int count = int(frame * animeSpeed) % animeTexture[0].size();
			IMAGEMANAGER->DrawTexture(animeTexture[0][count], {pos.x, pos.y});
		}
		else
		{
			IMAGEMANAGER->DrawTexture(animeTexture[0][(int)frame], {pos.x, pos.y});
		}
	}
}

void UI::Release()
{
}
