#include "Player.h"
#include "../Scene/Scene.h"
#include "../Input.h"
#include "../GameManager.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderSphere.h"
#include "../UI/UICharacterStateHUD.h"
#include "../UI/ProgressBar.h"
#include "../UI/UIText.h"
#include "PhantomBlow.h"
#include "BladeFury.h"

CPlayer::CPlayer() : m_Skill1Enable(false), m_Skill1Time(0.f)
{
}

CPlayer::CPlayer(const CPlayer& obj) : CCharacter(obj)
{
	
}

CPlayer::~CPlayer()
{
}

void CPlayer::Start()
{
	CCharacter::Start();

	CInput::GetInst()->SetCallback<CPlayer>("MoveLeft", KeyState_Push, this, &CPlayer::MoveLeft);
	CInput::GetInst()->SetCallback<CPlayer>("MoveRight", KeyState_Push, this, &CPlayer::MoveRight);
	CInput::GetInst()->SetCallback<CPlayer>("PhantomBlow", KeyState_Down, this, &CPlayer::PhantomBlow);
	CInput::GetInst()->SetCallback<CPlayer>("BladeFury", KeyState_Down, this, &CPlayer::BladeFury);
	CInput::GetInst()->SetCallback<CPlayer>("Jump", KeyState_Down, this, &CPlayer::JumpKey);
}

bool CPlayer::Init()
{
	if (!CCharacter::Init())
	{
		return false;
	}

	SetPivot(0.5f, 1.f);

	CreateAnimation();
	AddAnimation("PlayerRightIdle");
	AddAnimation("PlayerRightWalk", true, 0.6f);
	AddAnimation("PlayerRightAttack", false, 0.5f);
	AddAnimation("PlayerRightPhantomBlow", false);
	AddAnimation("PlayerRightBladeFury", false, 0.5f);

	AddAnimation("PlayerLeftIdle");
	AddAnimation("PlayerLeftWalk", true, 0.6f);
	AddAnimation("PlayerLeftAttack", false, 0.5f);
	AddAnimation("PlayerLeftPhantomBlow", false);
	AddAnimation("PlayerLeftBladeFury", false, 0.5f);

	SetAnimationEndNotify<CPlayer>("PlayerRightPhantomBlow", this, &CPlayer::AttackEnd);
	SetAnimationEndNotify<CPlayer>("PlayerLeftPhantomBlow", this, &CPlayer::AttackEnd);
	SetAnimationEndNotify<CPlayer>("PlayerRightBladeFury", this, &CPlayer::AttackEnd);
	SetAnimationEndNotify<CPlayer>("PlayerLeftBladeFury", this, &CPlayer::AttackEnd);

	CColliderSphere* Head = AddCollider<CColliderSphere>("Head");
	Head->SetRadius(20.f);
	Head->SetOffset(0.f, -50.f);
	Head->SetCollisionProfile("Player");

	CColliderBox* Body = AddCollider<CColliderBox>("Body");
	Body->SetExtent(80.f, 45.f);
	Body->SetOffset(0.f, -22.5f);
	Body->SetCollisionProfile("Player");

	m_StatusWidget = CreateWidgetComponent("StatusWidget");

	CProgressBar* Bar = m_StatusWidget->CreateWidget<CProgressBar>("HPBar");

	Bar->SetTexture("WorldHPBar", TEXT("CharacterHPBar.bmp"));
	
	m_StatusWidget->SetPos(-25.f, -95.f);

	m_CharacterInfo.HP = 1000;
	m_CharacterInfo.HPMax = 1000;

	m_CharacterInfo.MP = 1000;
	m_CharacterInfo.MPMax = 1000;

	//SetGravityAccel(30.f);
	SetPhysicsSimulate(true);
	SetJumpVelocity(70.f);
	SetSideWallCheck(true);

	return true;
}

void CPlayer::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);

	Vector2 Range = GetRange();

	if (m_Pos.x < 0.f)
	{
		m_Pos.x = 0;
	}

	if (m_Pos.x > Range.x + m_Size.x + (m_Size.x / 2))
	{
		m_Pos.x = Range.x + m_Size.x + (m_Size.x / 2);
	}

	if (CheckCurrentAnimation("PlayerRightPhantomBlow") || CheckCurrentAnimation("PlayerLeftPhantomBlow"))
	{
		SetOffset(0.f, 15.f);
	}

	else
	{
		SetOffset(0.f, 0.f);
	}
}

void CPlayer::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);

	bool Direction = GetDirection();

	// 현재 애니메이션이 Walk 상태에서 속도가 0이 되었다면 이전까지 움직이다가 지금 멈췄다는 것이다.
	if (CheckCurrentAnimation("PlayerRightWalk") && m_Velocity.Length() == 0.f && (!Direction))
	{
		ChangeAnimation("PlayerRightIdle");
	}

	if (CheckCurrentAnimation("PlayerLeftWalk") && m_Velocity.Length() == 0.f && (Direction))
	{
		ChangeAnimation("PlayerLeftIdle");
	}
}

void CPlayer::Collision(float DeltaTime)
{
	CCharacter::Collision(DeltaTime);
}

void CPlayer::Render(HDC hDC)
{
	CCharacter::Render(hDC);
}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}

float CPlayer::SetDamage(float Damage)
{
	Damage = CCharacter::SetDamage(Damage);

	CUICharacterStateHUD* State = m_Scene->FindUIWindow<CUICharacterStateHUD>("CharacterStateHUD");

	if (State)
	{
		State->SetHPPercent(m_CharacterInfo.HP / (float)m_CharacterInfo.HPMax);
	}

	CProgressBar* HPBar = (CProgressBar*)m_StatusWidget->GetWidget();

	HPBar->SetPercent(m_CharacterInfo.HP / (float)m_CharacterInfo.HPMax);

	return Damage;
}

void CPlayer::MoveUp(float DeltaTime)
{
	Move(Vector2(0.f, -1.f));
	ChangeAnimation("PlayerRightWalk");
}

void CPlayer::MoveDown(float DeltaTime)
{
	Move(Vector2(0.f, 1.f));
	ChangeAnimation("PlayerRightWalk");
}

void CPlayer::MoveLeft(float DeltaTime)
{
	Move(Vector2(-1.f, 0.f));

	SetDirection(true);

	ChangeAnimation("PlayerLeftWalk");
}

void CPlayer::MoveRight(float DeltaTime)
{
	Move(Vector2(1.f, 0.f));

	SetDirection(false);

	ChangeAnimation("PlayerRightWalk");
}

void CPlayer::PhantomBlow(float DeltaTime)
{
	bool Direction = GetDirection();

	if (Direction)
	{
		CPhantomBlow* Effect = m_Scene->CreateObject<CPhantomBlow>("LeftPhantomBlow", "LeftPhantomBlow", Vector2(m_Pos.x - m_Size.x, m_Pos.y - 50.f), Vector2(412.f, 210.f));

		ChangeAnimation("PlayerLeftPhantomBlow");
	}
	
	else
	{
		CPhantomBlow* Effect = m_Scene->CreateObject<CPhantomBlow>("RightPhantomBlow", "RightPhantomBlow", Vector2(m_Pos.x + m_Size.x, m_Pos.y - 50.f), Vector2(412.f, 210.f));

		ChangeAnimation("PlayerRightPhantomBlow");
	}	
}

void CPlayer::BladeFury(float DeltaTime)
{
	bool Direction = GetDirection();

	if (Direction)
	{
		CBladeFury* Effect = m_Scene->CreateObject<CBladeFury>("BladeFury", "BladeFury", Vector2(m_Pos.x, m_Pos.y - m_Size.y), Vector2(469.f, 195.f));

		ChangeAnimation("PlayerLeftBladeFury");
	}

	else
	{
		CBladeFury* Effect = m_Scene->CreateObject<CBladeFury>("BladeFury", "BladeFury", Vector2(m_Pos.x, m_Pos.y - m_Size.y), Vector2(469.f, 195.f));

		ChangeAnimation("PlayerRightBladeFury");
	}
}

void CPlayer::Pause(float DeltaTime)
{
	CGameManager::GetInst()->SetTimeScale(0.f);
}

void CPlayer::Resume(float DeltaTime)
{
	CGameManager::GetInst()->SetTimeScale(1.f);
}

void CPlayer::JumpKey(float DeltaTime)
{
	Jump();
}

void CPlayer::AttackEnd()
{
	if (m_Direction)
	{
		ChangeAnimation("PlayerLeftIdle");
	}

	else
	{
		ChangeAnimation("PlayerRightIdle");
	}
}

void CPlayer::SkillEnd()
{
	ChangeAnimation("PlayerRightIdle");
}

void CPlayer::Skill1Enable()
{
	CGameManager::GetInst()->SetTimeScale(0.01f);
	SetTimeScale(100.f);

	CUICharacterStateHUD* State = m_Scene->FindUIWindow<CUICharacterStateHUD>("CharacterStateHUD");

	m_CharacterInfo.MP -= 100;

	if (State)
	{
		State->SetMPPercent(m_CharacterInfo.MP / (float)m_CharacterInfo.HPMax);
	}

	m_Skill1Enable = true;
	//m_Skill1Time = 0.f;
}
