#include "PhantomBLow.h"
#include "Player.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"

CPhantomBlow::CPhantomBlow() : m_Direction(false)
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
		SetAnimationEndNotify<CPhantomBlow>("LeftPhantomBlow", this, &CPhantomBlow::AnimationFinish);
	}

	else
	{
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
	}

	else
	{
		CreateAnimation();
		AddAnimation("RightPhantomBlow", false);
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
