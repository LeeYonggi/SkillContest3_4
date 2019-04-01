#pragma once
#include "Object.h"
#include <functional>

class UI :
	public Object
{
public:
	UI(vector<Texture*> _animeTexture, Vector2 _pos, float _animeSpeed, bool isLoop, bool _isElaps);
	UI(Texture *up, Texture *down, Vector2 _pos, Vector2 size);
	UI() { }
	virtual ~UI();

public:
	float animeSpeed = 1.0f; 
	bool isButton;
	bool isElaps;
	bool isLoop;
	function<void()> func;
	Texture *downTex;
	Texture *upTex;
	bool isDown = false;


public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

