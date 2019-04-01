#include "DXUT.h"
#include "MeshManager.h"


MeshManager::MeshManager()
{
}


MeshManager::~MeshManager()
{
	Release();
}

CMeshLoader * MeshManager::AddMesh(string str, wstring file)
{
	auto iter = m_MeshLoaders.find(str);
	if (iter != m_MeshLoaders.end()) return iter->second;

	CMeshLoader *temp = new CMeshLoader;

	temp->Create(DEVICE, file.c_str());

	m_MeshLoaders.insert(make_pair(str, temp));

	return temp;
}

vector<CMeshLoader*> MeshManager::AddMeshAnime(string str, wstring file, int low, int high)
{
	vector<CMeshLoader*> temp;
	for (int i = low; i < high; i++)
	{
		WCHAR wctr[128];
		wsprintf(wctr, file.c_str(), i);
		temp.push_back(AddMesh(str + to_string(i), wctr));
	}
	return temp;
}

vector<Material*>* MeshManager::GetMaterialList(wstring str, vector<Material*>* material)
{
	auto iter = m_Materials.find(str);
	if (iter != m_Materials.end()) return iter->second;

	m_Materials.insert(make_pair(str, material));

	return nullptr;
}

void MeshManager::DrawMesh(CMeshLoader * meshLoader, Vector3 pos, Matrix matR, Vector3 scale, D3DXCOLOR color)
{
	Matrix matW, matS, matT;

	D3DXMatrixScaling(&matS, scale.x, scale.y, scale.z);
	D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);

	matW = matS * matR * matT;

	DEVICE->SetTransform(D3DTS_WORLD, &matW);

	DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	DEVICE->LightEnable(0, true);
	
	Vector3 dir = { 1.0, -1.0, 1.0 };
	D3DLIGHT9 light = d3d::GetDirectionalLight(&dir, &color);

	DEVICE->SetLight(0, &light);

	DEVICE->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	DEVICE->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	DEVICE->SetRenderState(D3DRS_SPECULARENABLE, true);

	for (int i = 0; i < meshLoader->GetNumMaterials(); i++)
	{
		D3DMATERIAL9 mtl = meshLoader->GetMaterial(i)->mtl;

		mtl.Ambient.a = meshLoader->GetMaterial(i)->fAlpha;
		mtl.Diffuse.a = meshLoader->GetMaterial(i)->fAlpha;
		mtl.Specular.a = meshLoader->GetMaterial(i)->fAlpha;
		mtl.Emissive = D3DXCOLOR(meshLoader->GetMaterial(i)->mtl.Diffuse) * 0.4f;
		mtl.Emissive.a = meshLoader->GetMaterial(i)->fAlpha;

		mtl.Power = 1.0f;

		DEVICE->SetMaterial(&mtl);
		DEVICE->SetTexture(0, meshLoader->GetMaterial(i)->pTexture);
		meshLoader->GetMesh()->DrawSubset(i);
	}
}

void MeshManager::DrawMesh(string str, Vector3 pos, Matrix matR, Vector3 scale)
{
	auto iter = m_MeshLoaders.find(str);
	if (iter == m_MeshLoaders.end()) return;
	DrawMesh(iter->second, pos, matR, scale);
}

void MeshManager::DrawAlphaMesh(CMeshLoader * meshLoader, Vector3 pos, Matrix matR, Vector3 scale)
{
	Matrix matW, matS, matT;

	D3DXMatrixScaling(&matS, scale.x, scale.y, scale.z);
	D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);

	matW = matS * matR * matT;

	DEVICE->SetTransform(D3DTS_WORLD, &matW);

	DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	DEVICE->LightEnable(0, true);

	Vector3 dir = { 1.0, -1.0, 1.0 };
	D3DLIGHT9 light = d3d::GetDirectionalLight(&dir, &D3DXCOLOR(1, 1, 1, 1));

	DEVICE->SetLight(0, &light);

	DEVICE->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	DEVICE->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	DEVICE->SetRenderState(D3DRS_SPECULARENABLE, true);

	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);


	for (int i = 0; i < meshLoader->GetNumMaterials(); i++)
	{
		D3DMATERIAL9 mtl = meshLoader->GetMaterial(i)->mtl;

		mtl.Ambient.a = meshLoader->GetMaterial(i)->fAlpha;
		mtl.Diffuse.a = meshLoader->GetMaterial(i)->fAlpha;
		mtl.Specular.a = meshLoader->GetMaterial(i)->fAlpha;
		mtl.Emissive = D3DXCOLOR(meshLoader->GetMaterial(i)->mtl.Diffuse) * 1.0f;
		mtl.Emissive.a = meshLoader->GetMaterial(i)->fAlpha;

		mtl.Power = 1.0f;

		DEVICE->SetMaterial(&mtl);
		DEVICE->SetTexture(0, meshLoader->GetMaterial(i)->pTexture);
		meshLoader->GetMesh()->DrawSubset(i);
	}

	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BOTHINVSRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_BOTHINVSRCALPHA);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

void MeshManager::DrawEffect(CMeshLoader * meshLoader, Texture *texture, Vector3 pos, Matrix matR, Vector3 scale)
{
	Matrix matW, matS, matT;

	D3DXMatrixScaling(&matS, scale.x, scale.y, scale.z);
	D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);

	matW = matS * matR * matT;

	DEVICE->SetTransform(D3DTS_WORLD, &matW);

	DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	DEVICE->LightEnable(0, true);

	Vector3 dir = { 1.0, -1.0, 1.0 };
	D3DLIGHT9 light = d3d::GetDirectionalLight(&dir, &D3DXCOLOR(1, 1, 1, 1));

	DEVICE->SetLight(0, &light);

	DEVICE->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	DEVICE->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	DEVICE->SetRenderState(D3DRS_SPECULARENABLE, true);

	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, false);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	for (int i = 0; i < meshLoader->GetNumMaterials(); i++)
	{
		D3DMATERIAL9 mtl = meshLoader->GetMaterial(i)->mtl;

		mtl.Ambient.a = meshLoader->GetMaterial(i)->fAlpha;
		mtl.Diffuse.a = meshLoader->GetMaterial(i)->fAlpha;
		mtl.Specular.a = meshLoader->GetMaterial(i)->fAlpha;
		mtl.Emissive = D3DXCOLOR(meshLoader->GetMaterial(i)->mtl.Diffuse) * 1.0f;
		mtl.Emissive.a = meshLoader->GetMaterial(i)->fAlpha;

		mtl.Power = 1.0f;

		DEVICE->SetMaterial(&mtl);
		DEVICE->SetTexture(0, texture->tex);
		meshLoader->GetMesh()->DrawSubset(i);
	}
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, true);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BOTHINVSRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_BOTHINVSRCALPHA);
}

void MeshManager::Release()
{
	for (auto iter : m_Materials)
	{
		for (auto _iter : *iter.second)
		{
			SAFE_DELETE(_iter);
		}
		iter.second->clear();
		SAFE_DELETE(iter.second);
	}
	m_Materials.clear();
	for (auto iter : m_MeshLoaders)
	{
		SAFE_DELETE(iter.second);
	}
	m_MeshLoaders.clear();
}
