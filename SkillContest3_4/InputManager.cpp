#include "DXUT.h"
#include "InputManager.h"


InputManager::InputManager()
{
	Init();
}


InputManager::~InputManager()
{
}

void InputManager::Init()
{
	memset(nowKey, false, sizeof(nowKey));
	memset(pastKey, false, sizeof(pastKey));

	mouse = { 0, 0 };
}

void InputManager::Update()
{
	memcpy(pastKey, nowKey, sizeof(nowKey));

	for (int i = 0; i < KEY_MAX; ++i)
		nowKey[i] = GetAsyncKeyState(i);

	GetCursorPos(&mouse);
	ScreenToClient(DXUTGetHWND(), &mouse);
}
