#include "Shadowblade.h"

CShadowBlade::CShadowBlade()
{
}

CShadowBlade::CShadowBlade(const CShadowBlade& obj) : CCharacter(obj)
{
}

CShadowBlade::~CShadowBlade()
{
}

void CShadowBlade::Start()
{
	CCharacter::Start();
}

bool CShadowBlade::Init()
{
	if (!CCharacter::Init())
	{
		return false;
	}

	SetPivot(0.5f, 1.f);

	CreateAnimation();
	AddAnimation("RightShadowBladeStand");
	AddAnimation("LeftShadowBladeStand");
	AddAnimation("RightShadowBladeMove");
	AddAnimation("LeftShadowBladeMove");

	return true;
}

void CShadowBlade::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);
}

void CShadowBlade::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);
}

void CShadowBlade::Collision(float DeltaTime)
{
	CCharacter::Collision(DeltaTime);
}

void CShadowBlade::Render(HDC hDC)
{
	CCharacter::Render(hDC);
}

CShadowBlade* CShadowBlade::Clone()
{
	return new CShadowBlade(*this);
}
