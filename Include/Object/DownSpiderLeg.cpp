#include "DownSpiderLeg.h"
#include "Player.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "../Scene/MainMap.h"
#include "../Collision/ColliderBox.h"

CDownSpiderLeg::CDownSpiderLeg()
{
}

CDownSpiderLeg::CDownSpiderLeg(const CDownSpiderLeg& obj) : CGameObject(obj)
{
}

CDownSpiderLeg::~CDownSpiderLeg()
{
}

void CDownSpiderLeg::Start()
{
	CGameObject::Start();

	SetAnimationEndNotify<CDownSpiderLeg>("DownSpiderLeg", this, &CDownSpiderLeg::AnimationFinish);

	AddAnimationNotify<CDownSpiderLeg>("DownSpiderLeg", 21, this, &CDownSpiderLeg::Attack);
}

bool CDownSpiderLeg::Init(bool Direction)
{
	if (!CGameObject::Init())
	{
		return false;
	}

	SetPivot(0.5f, 1.f);

	CreateAnimation();
	AddAnimation("DownSpiderLeg", false, 2.0f);

	return true;
}

void CDownSpiderLeg::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CDownSpiderLeg::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CDownSpiderLeg::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CDownSpiderLeg::Render(HDC hDC)
{
	CGameObject::Render(hDC);
}

CDownSpiderLeg* CDownSpiderLeg::Clone()
{
	return new CDownSpiderLeg(*this);
}

void CDownSpiderLeg::AnimationFinish()
{
	Destroy();
}

void CDownSpiderLeg::Attack()
{
	CColliderBox* Body = AddCollider<CColliderBox>("Body");
	Body->SetExtent(60.f, 720.f);
	Body->SetOffset(-60.f, -500.f);
	Body->SetCollisionProfile("MonsterAttack");

	CCollider* ColliderBody = FindCollider("Body");

	Body->SetCollisionBeginFunction<CDownSpiderLeg>(this, &CDownSpiderLeg::ColliderBegin);
}

void CDownSpiderLeg::ColliderBegin(CCollider* Src, CCollider* Dest, float DeltaTime)
{
	if (Dest->GetProfile()->Name == "Player")
	{

	}
}
