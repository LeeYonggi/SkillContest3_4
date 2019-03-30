#pragma once
#include "Scene.h"
#include <thread>

#define ANIMEFRAME 1
class LoadScene :
	public Scene
{
public:
	LoadScene();
	virtual ~LoadScene();

private:
	thread loading;
	bool isEndLoading;

public:
	virtual void Init()		override;
	void Loading();
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

