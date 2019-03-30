#pragma once
#include "Singleton.h"
class MeshManager :
	public Singleton<MeshManager>
{
public:
	MeshManager();
	virtual ~MeshManager();

private:
	map<string, CMeshLoader*> m_MeshLoaders;
	map<wstring, vector<Material*>*> m_Materials;

public:
	CMeshLoader *AddMesh(string str, wstring file);
	vector<CMeshLoader*> AddMeshAnime(string str, wstring file, int low, int high);
	vector<Material*> *GetMaterialList(wstring str, vector<Material*> *material);
	void DrawMesh(CMeshLoader *meshLoader, Vector3 pos, Matrix matR, Vector3 scale = { 1, 1, 1 });
	void DrawMesh(string str, Vector3 pos, Matrix matR, Vector3 scale = { 1, 1, 1 });
	void DrawAlphaMesh(CMeshLoader *meshLoader, Vector3 pos, Matrix matR, Vector3 scale = { 1, 1, 1 });
	void DrawEffect(CMeshLoader *meshLoader, Texture *texture, Vector3 pos, Matrix matR, Vector3 scale = { 1, 1, 1 });

	void Release();
};

#define MESHMANAGER MeshManager::GetInstance()