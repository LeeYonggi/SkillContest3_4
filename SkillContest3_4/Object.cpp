#include "DXUT.h"
#include "Object.h"

#include "Particle.h"

Object::Object()
{
	D3DXMatrixIdentity(&matR);
	D3DXQuaternionIdentity(&quaternion);
}


Object::~Object()
{
	animeMesh.clear();
	animeTexture.clear();
	for (auto iter : vParticle)
		iter->isDestroy = true;
	vParticle.clear();
}

void Object::RotateLerp(Vector3 eye, Vector3 at, Matrix * mat)
{
	Matrix tempMat;
	D3DXQUATERNION tempQuater;
	D3DXMatrixLookAtLH(&tempMat, &eye, &at, &Vector3(0, 1, 0));
	D3DXMatrixTranspose(&tempMat, &tempMat);

	D3DXQuaternionRotationMatrix(&tempQuater, &tempMat);
	D3DXQuaternionSlerp(&quaternion, &quaternion, &tempQuater, 0.1f);
	D3DXMatrixRotationQuaternion(mat, &quaternion);
}

bool Object::GetPixelCollision(Vector2 p1, Texture * tex)
{
	bool isCollision = false;
	D3DLOCKED_RECT lockRect = { 0 };

	tex->tex->LockRect(0, &lockRect, nullptr, D3DLOCK_DISCARD);
	
	int x = p1.x;
	int y = (tex->info.Height * 0.5f) - p1.y;

	if (x < 0 || x > tex->info.Width ||
		y < 0 || y > tex->info.Height)
	{
		tex->tex->UnlockRect(0);
		return false;
	}
	
	DWORD *bit = (DWORD*)lockRect.pBits;

	D3DXCOLOR color = bit[(tex->info.Width * y) + x];
	if (color == D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f))
		isCollision = true;

	tex->tex->UnlockRect(0);
	return isCollision;
}

Vector3 Object::GetTargetVec3(Vector3 p1, Vector3 p2)
{
	Vector3 temp = p2 - p1;
	D3DXVec3Normalize(&temp, &temp);
	return temp;
}

Matrix Object::GetBillboard(Vector3 p1, Vector3 p2)
{
	Vector3 temp = p2 - p1;
	D3DXVec3Normalize(&temp, &temp);

	Matrix mat, tempMatR;
	D3DXMatrixLookAtLH(&mat, &Vector3(0, 0, 0), &temp, &Vector3(0, 1, 0));
	D3DXMatrixRotationX(&tempMatR, D3DXToRadian(-90));
	mat *= tempMatR;
	return mat;
}

bool Object::GetCircleCollision(Vector3 p1, Vector3 p2, float r1, float r2)
{
	Vector3 temp = p2 - p1;
	float length = temp.x * temp.x + temp.y * temp.y;
	float d = length + temp.z * temp.z;
	return (sqrt(d) < r1 + r2);
}
