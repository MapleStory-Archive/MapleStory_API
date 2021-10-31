#pragma once
#include "GameObject.h"
class CDownSpiderLeg :
    public CGameObject
{
	friend class CScene;

public:
	CDownSpiderLeg();
	CDownSpiderLeg(const CDownSpiderLeg& obj);
	virtual ~CDownSpiderLeg();

public:
	virtual void Start();
	virtual bool Init(bool Direction);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CDownSpiderLeg* Clone();

public:
	void AnimationFinish();
	void Attack();

	void ColliderBegin(class CCollider* Src, class CCollider* Dest, float DeltaTime);
};

