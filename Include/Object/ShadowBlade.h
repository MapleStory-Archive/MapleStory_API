#pragma once

#include "Character.h"

class CShadowBlade :
    public CCharacter
{
	friend class CScene;

public:
	CShadowBlade();
	CShadowBlade(const CShadowBlade& obj);
	virtual ~CShadowBlade();

private:
	Vector2 m_Dir;
	float m_FireTime;
	float m_FireTimeMax;
	int m_Count;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CShadowBlade* Clone();
};

