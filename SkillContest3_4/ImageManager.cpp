#include "DXUT.h"
#include "ImageManager.h"


ImageManager::ImageManager()
{
	D3DXCreateSprite(DEVICE, &sprite);
}


ImageManager::~ImageManager()
{
	Release();
	SAFE_RELEASE(sprite);
}

Texture * ImageManager::AddTexture(wstring str, wstring file)
{
	auto iter = m_Texture.find(str);
	if (iter != m_Texture.end()) return iter->second;

	Texture *temp = new Texture;
	
	D3DXCreateTextureFromFileEx(DEVICE, 
		file.c_str(), 
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		0, 0, 
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, 0,
		&temp->info,
		nullptr,
		&temp->tex);

	m_Texture.insert(make_pair(str, temp));

	return temp;
}

vector<Texture*> ImageManager::AddAnimeTexture(wstring str, wstring file, int low, int high)
{
	vector<Texture*> temp;
	for (int i = low; i <= high; i++)
	{
		WCHAR wctr[128];
		wsprintf(wctr, file.c_str(), i);
		temp.push_back(AddTexture(str + to_wstring(i), wctr));
	}

	return temp;
}

void ImageManager::DrawTexture(Texture * texture, Vector2 pos, float scale, float angle, D3DXCOLOR color)
{
	Matrix matW, matR, matS, matT;
	D3DXMatrixScaling(&matS, scale, scale, scale);
	D3DXMatrixRotationZ(&matR, angle);
	D3DXMatrixTranslation(&matT, pos.x, pos.y, 0);

	matW = matS * matR * matT;

	sprite->SetTransform(&matW);

	Vector3 center = { (float)(texture->info.Width * 0.5), (float)(texture->info.Height * 0.5), 0 };

	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	sprite->Draw(texture->tex, nullptr, &center, nullptr, color);

	sprite->End();
}

void ImageManager::DrawFont(string str, Vector2 pos, float scale)
{
	LPD3DXFONT font;
	D3DXCreateFontA(DEVICE, scale, 0, FW_HEAVY, 1, false, HANGUL_CHARSET, 0, 0, 0, "¸¼Àº °íµñ", &font);

	Matrix mat;
	D3DXMatrixTranslation(&mat, pos.x, pos.y, 0);
	
	sprite->SetTransform(&mat);

	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT re = { 0 };

	font->DrawTextA(sprite, str.c_str(), -1, &re, DT_NOCLIP, D3DXCOLOR(1, 1, 1, 1));

	sprite->End();

	SAFE_RELEASE(font);
}

void ImageManager::Release()
{
	for (auto iter : m_Texture)
	{
		SAFE_RELEASE(iter.second->tex);
		SAFE_DELETE(iter.second);
	}
	m_Texture.clear();
}
