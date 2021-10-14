#pragma once
#include "Character.h"

class CPlayer :
    public CCharacter
{
	friend class CScene;

public:
	CPlayer();
	CPlayer(const CPlayer& obj);
	virtual ~CPlayer();

protected:
	bool m_Skill1Enable;
	float m_Skill1Time;
	CSharedPtr<CWidgetComponent> m_HPBarWidget;
	CSharedPtr<CWidgetComponent> m_NameWidget;

public: 
	void SetAttackSpeed(float Speed)
	{
		CCharacter::SetAttackSpeed(Speed);
 		SetAnimationPlayScale("LucidNunNaRightAttack", Speed);
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CPlayer* Clone();
	virtual float SetDamage(float Damage);

public:
	void MoveUp(float DeltaTime);
	void MoveDown(float DeltaTime);
	void MoveLeft(float DeltaTime);
	void MoveRight(float DeltaTime);
	void PhantomBlow(float DeltaTime);
	void Pause(float DeltaTime);
	void Resume(float DeltaTime);
	void Skill1(float DeltaTime);
	void JumpKey(float DeltaTime);

public:
	void AttackEnd();

	void SkillEnd();
	void Skill1Enable();
};

