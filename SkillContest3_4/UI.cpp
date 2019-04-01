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

UI::UI(Texture * up, Texture * down, Vector2 _pos, Vector2 size, function<void()> func)
{
	isButton = true;
	upTex = up;
	downTex = down;
	pos.x = _pos.x;
	pos.y = _pos.y;
	this->func = func;
	this->size.x = size.x;
	this->size.y = size.y;
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
		isDown = false;
		if (GetRectCollision({ (int)pos.x, (int)pos.y }, size))
		{
			isDown = true;
			if (INPUTMANAGER->KeyDown(VK_LBUTTON))
			{
				func();
			}
		}
	}
	else
	{
		if (isElaps)
		{
			frame += ELTIME;
			if (!isLoop && frame * animeSpeed >= animeTexture[0].size())
			{
				isActive = false;
			}
		}
		else
		{
			frame += animeSpeed;
			if (!isLoop && frame >= animeTexture[0].size())
			{
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
			IMAGEMANAGER->DrawTexture(animeTexture[0][(int)frame % animeTexture[0].size()], {pos.x, pos.y});
		}
	}
}

void UI::Release()
{
}

bool UI::GetRectCollision(POINT p1, POINT size)
{
	RECT re = { p1.x - size.x * 0.5, p1.y - size.y * 0.5, 
		p1.x + size.x * 0.5, p1.y + size.y * 0.5 };
	RECT mouse = { INPUTMANAGER->GetMouse().x, INPUTMANAGER->GetMouse().y,
		INPUTMANAGER->GetMouse().x + 1,INPUTMANAGER->GetMouse().y + 1 };
	RECT re2 = { 0 };
	return IntersectRect(&re2, &re, &mouse);
}
