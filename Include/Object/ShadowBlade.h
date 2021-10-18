#pragma once

#include "Monster.h"

class CShadowBlade :
    public CMonster
{
	friend class CScene;

private:
	bool m_IsAttack;
	bool m_IsAttackAni;

public:
	CShadowBlade();
	CShadowBlade(const CShadowBlade& obj);
	virtual ~CShadowBlade();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CShadowBlade* Clone();

protected:
	virtual void AIIdle(float DeltaTime);
	virtual void AIMove(float DeltaTime);
	virtual void AITrace(float DeltaTime);
	virtual void AIAttack(float DeltaTime);
	virtual void AIDeath(float DeltaTime);

public:
	void CollisionTargetBegin(class CCollider* Src, class CCollider* Dest, float DeltaTime);
	void CollisionTargetEnd(class CCollider* Src, class CCollider* Dest, float DeltaTime);

	void CollisionAttackBegin(class CCollider* Src, class CCollider* Dest, float DeltaTime);
	void CollisionAttackEnd(class CCollider* Src, class CCollider* Dest, float DeltaTime);

	void AttackAnimationStart();
	void AttackAnimationEnd();
};

