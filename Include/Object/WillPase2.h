#pragma once

#include "Monster.h"

class CWillPase2 :
    public CMonster
{
	friend class CScene;

public:
	CWillPase2();
	CWillPase2(const CWillPase2& obj);
	virtual ~CWillPase2();

private:
	CSharedPtr<CWidgetComponent> m_StatusWidget;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CWillPase2* Clone();
	virtual float SetDamage(float Damage);

protected:
	virtual void AIIdle(float DeltaTime);
	virtual void AIMove(float DeltaTime);
	virtual void AIAttack(float DeltaTime);
	virtual void AIDeath(float DeltaTime);

public:
	void CollisionAttackBegin(class CCollider* Src, class CCollider* Dest, float DeltaTime);
	void CollisionAttackEnd(class CCollider* Src, class CCollider* Dest, float DeltaTime);

	void AttackAnimationStart();
	void AttackAnimationEnd();

	void AttackStart();
	void AttackEnd();
};

