#pragma once

#include "GameObject.h"

class CPhantomBlow :
	public CGameObject
{
	friend class CScene;

protected:
	CPhantomBlow();
	CPhantomBlow(const CPhantomBlow& obj);
	virtual ~CPhantomBlow();

private:
	bool m_Direction;

public:
	virtual void Start();
	virtual bool Init(bool Direction);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CPhantomBlow* Clone();

public:
	void ChangeAnimation(bool Direction);
	void AnimationFinish();
};

