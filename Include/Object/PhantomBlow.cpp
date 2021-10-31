#include "PhantomBLow.h"
#include "Player.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"
#include "DamageFont.h"

CPhantomBlow::CPhantomBlow() : m_Direction(false), m_IsHit(false)
{
	m_ObjType = EObject_Type::Effect;
}

CPhantomBlow::CPhantomBlow(const CPhantomBlow& obj) : CGameObject(obj)
{
	m_Direction = obj.m_Direction;
}

CPhantomBlow::~CPhantomBlow()
{
}

void CPhantomBlow::Start()
{
	CGameObject::Start();

	if (m_Direction)
	{
		CCollider* Body = FindCollider("Body");

		Body->SetCollisionBeginFunction<CPhantomBlow>(this, &CPhantomBlow::ColliderBegin);

		SetAnimationEndNotify<CPhantomBlow>("LeftPhantomBlow", this, &CPhantomBlow::AnimationFinish);
	}

	else
	{
		CCollider* Body = FindCollider("Body");

		Body->SetCollisionBeginFunction<CPhantomBlow>(this, &CPhantomBlow::ColliderBegin);

		SetAnimationEndNotify<CPhantomBlow>("RightPhantomBlow", this, &CPhantomBlow::AnimationFinish);
	}
	
}

bool CPhantomBlow::Init(bool Direction)
{
	if (!CGameObject::Init())
	{
		return false;
	}

	m_Direction = Direction;

	SetPivot(0.5f, 0.5f);

	if (m_Direction)
	{
		CreateAnimation();
		AddAnimation("LeftPhantomBlow", false);

		CColliderBox* Body = AddCollider<CColliderBox>("Body");
		Body->SetExtent(230.f, 130.f);
		Body->SetOffset(-80.f, 0.f);
		Body->SetCollisionProfile("PlayerAttack");
	}

	else
	{
		CreateAnimation();
		AddAnimation("RightPhantomBlow", false);

		CColliderBox* Body = AddCollider<CColliderBox>("Body");
		Body->SetExtent(230.f, 130.f);
		Body->SetOffset(80.f, 0.f);
		Body->SetCollisionProfile("PlayerAttack");
	}

	return true;
}

void CPhantomBlow::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CPhantomBlow::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CPhantomBlow::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CPhantomBlow::Render(HDC hDC)
{
	CGameObject::Render(hDC);
}

CPhantomBlow* CPhantomBlow::Clone()
{
	return new CPhantomBlow(*this);
}

void CPhantomBlow::ChangeAnimation(bool Direction)
{
	
}

void CPhantomBlow::AnimationFinish()
{
	Destroy();
}

void CPhantomBlow::ColliderBegin(CCollider* Src, CCollider* Dest, float DeltaTime)
{
	if (Dest->GetProfile()->Name == "Monster")
	{
		m_IsHit = true;

		for (int i = 0; i < 6; i++)
		{
			if (m_Direction)
			{
				AddAnimationNotify<CPhantomBlow>("LeftPhantomBlow", i, this, &CPhantomBlow::Attack);
			}

			else
			{
				AddAnimationNotify<CPhantomBlow>("RightPhantomBlow", i, this, &CPhantomBlow::Attack);
			}
		}
	}
}

void CPhantomBlow::Attack()
{
	CGameObject* Monster = m_Scene->FindObject("Monster");

	Vector2 Pos = Monster->GetPos();

	Vector2 Size = Monster->GetSize();

	int Frame = m_Animation->GetFrame();

	Monster->SetDamage(10);

	CDamageFont* DamageFont = m_Scene->CreateDamageFont<CDamageFont>("DamageFont", Vector2(Pos.x - 31.f, Pos.y - (Size.y / 2) - (Frame * 30)));

	DamageFont->SetDamageNumber(10);
}
