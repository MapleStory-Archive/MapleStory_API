#include "UpSpiderLeg.h"
#include "Player.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "../Scene/MainMap.h"
#include "../Collision/ColliderBox.h"

CUpSpiderLeg::CUpSpiderLeg()
{
	m_ObjType = EObject_Type::GameObject;
}

CUpSpiderLeg::CUpSpiderLeg(const CUpSpiderLeg& obj) : CGameObject(obj)
{
}

CUpSpiderLeg::~CUpSpiderLeg()
{
}

void CUpSpiderLeg::Start()
{
	CGameObject::Start();

	SetAnimationEndNotify<CUpSpiderLeg>("UpSpiderLeg", this, &CUpSpiderLeg::AnimationFinish);

	AddAnimationNotify<CUpSpiderLeg>("UpSpiderLeg", 21, this, &CUpSpiderLeg::Attack);
}

bool CUpSpiderLeg::Init(bool Direction)
{
	if (!CGameObject::Init())
	{
		return false;
	}

	SetPivot(0.5f, 0.f);

	CreateAnimation();
	AddAnimation("UpSpiderLeg", false, 2.0f);

	return true;
}

void CUpSpiderLeg::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CUpSpiderLeg::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CUpSpiderLeg::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CUpSpiderLeg::Render(HDC hDC)
{
	CGameObject::Render(hDC);
}

CUpSpiderLeg* CUpSpiderLeg::Clone()
{
	return new CUpSpiderLeg(*this);
}

void CUpSpiderLeg::AnimationFinish()
{
	Destroy();
}

void CUpSpiderLeg::Attack()
{
	CColliderBox* Body = AddCollider<CColliderBox>("Body");
	Body->SetExtent(60.f, 1440.f);
	Body->SetOffset(-60.f, 0.f);
	Body->SetCollisionProfile("MonsterAttack");

	CCollider* ColliderBody = FindCollider("Body");

	Body->SetCollisionBeginFunction<CUpSpiderLeg>(this, &CUpSpiderLeg::ColliderBegin);
}

void CUpSpiderLeg::ColliderBegin(CCollider* Src, CCollider* Dest, float DeltaTime)
{
	if (Dest->GetProfile()->Name == "Player")
	{

	}
}
