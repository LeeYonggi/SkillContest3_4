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
	LPD3DXSPRITE sprite;

public:
	Texture *AddTexture(wstring str, wstring file);
	vector<Texture*> AddAnimeTexture(wstring str, wstring file, int low, int high);
	void DrawTexture(Texture *texture, Vector2 pos, float scale = 1, float angle = 0, D3DXCOLOR color = { 1, 1, 1, 1});
	void DrawFont(string str, Vector2 pos, float scale);

	void Release();
};

#define IMAGEMANAGER ImageManager::GetInstance()