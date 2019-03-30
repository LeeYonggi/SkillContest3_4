#pragma once
#include "Singleton.h"

#define KEY_MAX 256
class InputManager :
	public Singleton<InputManager>
{
public:
	InputManager();
	virtual ~InputManager();

private:
	bool nowKey[KEY_MAX];
	bool pastKey[KEY_MAX];
	POINT mouse;

public:
	void Init();
	void Update();

public:
	bool KeyDown(int key)  { return (pastKey[key] == false && nowKey[key] == true); }
	bool KeyPress(int key) { return (pastKey[key] == true  && nowKey[key] == true); }
	bool KeyUp(int key)    { return (pastKey[key] == true && nowKey[key] == false); }

	POINT GetMouse() { return mouse; }

};

#define INPUTMANAGER InputManager::GetInstance()