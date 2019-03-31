#pragma once

#define GRAVITY_SCALE 0.02
class Particle;
class Object
{
public:
	Object();
	virtual ~Object();

public:
	Vector3 pos = { 0, 0, 0 };
	Vector3 scale = { 1, 1, 1 };
	Matrix matR;
	CMeshLoader *mesh;
	Texture *texture;
	vector<vector<CMeshLoader*>> animeMesh;
	vector<vector<Texture*>> animeTexture;
	D3DXQUATERNION quaternion;
	Vector3 moveVector = { 1, 0, 0 };
	vector<Particle*> vParticle;
	bool isDestroy = false;
	bool isActive = true;
	float frame = 0.0f;

public:
	virtual void Init()		PURE;
	virtual void Update()	PURE;
	virtual void Render()	PURE;
	virtual void Release()	PURE;

public:
	void RotateLerp(Vector3 eye, Vector3 at, Matrix *mat);
	bool GetPixelCollision(Vector2 p1, Texture *tex);
	Vector3 GetTargetVec3(Vector3 p1, Vector3 p2);
	Matrix GetBillboard(Vector3 p1, Vector3 p2);
};

