#pragma once

#include "GameObject.h"

class CUpSpiderLeg :
    public CGameObject
{
	friend class CScene;

public:
	CUpSpiderLeg();
	CUpSpiderLeg(const CUpSpiderLeg& obj);
	virtual ~CUpSpiderLeg();

public:
	virtual void Start();
	virtual bool Init(bool Direction);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CUpSpiderLeg* Clone();

public:
	void AnimationFinish();
	void Attack();

	void ColliderBegin(class CCollider* Src, class CCollider* Dest, float DeltaTime);
};

