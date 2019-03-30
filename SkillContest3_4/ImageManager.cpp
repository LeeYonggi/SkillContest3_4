#include "DXUT.h"
#include "ImageManager.h"


ImageManager::ImageManager()
{
}


ImageManager::~ImageManager()
{
	Release();
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

void ImageManager::Release()
{
	for (auto iter : m_Texture)
	{
		SAFE_RELEASE(iter.second->tex);
		SAFE_DELETE(iter.second);
	}
	m_Texture.clear();
}
