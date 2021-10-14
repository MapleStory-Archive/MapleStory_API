#pragma once

#include "Scene.h"

class CTutorialMap :
    public CScene
{
	friend class CSceneManager;

private:
	CTutorialMap();
	virtual ~CTutorialMap();

public:
	virtual bool Init();

private:
	void LoadAnimationSequence();
	void LoadSound();
};

