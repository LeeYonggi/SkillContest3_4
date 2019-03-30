#pragma once
#include "Singleton.h"

struct Texture
{
	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 tex;
};
class ImageManager :
	public Singleton<ImageManager>
{
public:
	ImageManager();
	virtual ~ImageManager();

private:
	map<wstring, Texture*> m_Texture;

public:
	Texture *AddTexture(wstring str, wstring file);

	void Release();
};

#define IMAGEMANAGER ImageManager::GetInstance()