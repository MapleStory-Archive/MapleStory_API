#include "WillPase2.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"
#include "../UI/UIBossWillPase2.h"
#include "../UI/ProgressBar.h"

CWillPase2::CWillPase2()
{
}

CWillPase2::CWillPase2(const CWillPase2& obj) : CMonster(obj)
{
}

CWillPase2::~CWillPase2()
{
}

void CWillPase2::Start()
{
	CMonster::Start();

	CCollider* AttackSense = FindCollider("AttackSense");

	AttackSense->SetCollisionBeginFunction<CWillPase2>(this, &CWillPase2::CollisionAttackBegin);
	AttackSense->SetCollisionEndFunction<CWillPase2>(this, &CWillPase2::CollisionAttackEnd);

	AddAnimationNotify<CWillPase2>("RightWillAttack1", 20, this, &CWillPase2::AttackEnd);
	AddAnimationNotify<CWillPase2>("RightWillAttack2", 20, this, &CWillPase2::AttackEnd);
	AddAnimationNotify<CWillPase2>("RightWillAttack3", 20, this, &CWillPase2::AttackEnd);
	AddAnimationNotify<CWillPase2>("RightWillAttack4", 30, this, &CWillPase2::AttackEnd);
	AddAnimationNotify<CWillPase2>("RightWillAttack5", 20, this, &CWillPase2::AttackEnd);
	AddAnimationNotify<CWillPase2>("RightWillAttack6", 20, this, &CWillPase2::AttackEnd);
	AddAnimationNotify<CWillPase2>("RightWillAttack7", 16, this, &CWillPase2::AttackEnd);

	AddAnimationNotify<CWillPase2>("LeftWillAttack1", 20, this, &CWillPase2::AttackEnd);
	AddAnimationNotify<CWillPase2>("LeftWillAttack2", 20, this, &CWillPase2::AttackEnd);
	AddAnimationNotify<CWillPase2>("LeftWillAttack3", 20, this, &CWillPase2::AttackEnd);
	AddAnimationNotify<CWillPase2>("LeftWillAttack4", 30, this, &CWillPase2::AttackEnd);
	AddAnimationNotify<CWillPase2>("LeftWillAttack5", 20, this, &CWillPase2::AttackEnd);
	AddAnimationNotify<CWillPase2>("LeftWillAttack6", 20, this, &CWillPase2::AttackEnd);
	AddAnimationNotify<CWillPase2>("LeftWillAttack7", 16, this, &CWillPase2::AttackEnd);
}

bool CWillPase2::Init()
{
	if (!CMonster::Init())
	{
		return false;
	}

	SetPivot(0.5f, 0.5f);

	CreateAnimation();
	AddAnimation("RightWill");
	AddAnimation("RightWillMove", true, 2.0f);
	AddAnimation("RightWillAttack1", true, 2.0f);
	AddAnimation("RightWillAttack2", true, 2.0f);
	AddAnimation("RightWillAttack3", true, 2.0f);
	AddAnimation("RightWillAttack4", true, 2.0f);
	AddAnimation("RightWillAttack5", true, 2.0f);
	AddAnimation("RightWillAttack6", true, 2.0f);
	AddAnimation("RightWillAttack7", true, 1.5f);

	AddAnimation("LeftWill");
	AddAnimation("LeftWillMove", true, 2.0f);
	AddAnimation("LeftWillAttack1", true, 2.0f);
	AddAnimation("LeftWillAttack2", true, 2.0f);
	AddAnimation("LeftWillAttack3", true, 2.0f);
	AddAnimation("LeftWillAttack4", true, 2.0f);
	AddAnimation("LeftWillAttack5", true, 2.0f);
	AddAnimation("LeftWillAttack6", true, 2.0f);
	AddAnimation("LeftWillAttack7", true, 1.5f);

	CColliderBox* Body = AddCollider<CColliderBox>("Body");
	Body->SetExtent(m_Size.x, 365.f);
	Body->SetCollisionProfile("Monster");

	CColliderBox* AttackSense = AddCollider<CColliderBox>("AttackSense");
	AttackSense->SetExtent(500, m_Size.y * 2.f);
	AttackSense->SetOffset(0.f, -m_Size.y / 2.f);

	m_MoveSpeed = 100.f;

	m_CharacterInfo.HP = 100;
	m_CharacterInfo.HPMax = 100;

	return true;
}

void CWillPase2::Update(float DeltaTime)
{
	CMonster::Update(DeltaTime);

	CUIBossWillPase2* State = m_Scene->FindUIWindow<CUIBossWillPase2>("WillStateHUD");

	if (State)
	{
		State->SetHPPercent1(m_CharacterInfo.HP / (float)m_CharacterInfo.HPMax);
	}

	Vector2 Range = GetRange();

	if (m_Pos.x <= 0.f)
	{
		m_Pos.x = 0.f;
	}

	if (m_Pos.x > Range.x + m_Size.x + (m_Size.x / 2))
	{
		m_Pos.x = Range.x + m_Size.x + (m_Size.x / 2);
	}

	m_ActiveTime += DeltaTime;

	if (m_ActiveTime > m_RandActive)
	{
		if (m_IsAttack)
		{
			m_IsMove = rand() % 3;
		}

		else
		{
			m_IsMove = rand() % 2;
		}

		if (!m_IsAttackAni)
		{
			m_ActiveTime = 0.f;

			if (m_IsMove == 0)
			{
				CGameObject* Player = m_Scene->GetPlayer();

				Vector2	Dir = Player->GetPos() - m_Pos;
				Dir.Normalize();

				if (Dir.x < 0)
				{
					m_Direction = true;
				}

				else
				{
					m_Direction = false;
				}

				m_AI = EMonsterAI::Move;
			}

			else if (m_IsMove == 1)
			{
				m_AI = EMonsterAI::Idle;
			}

			else
			{
				CGameObject* Player = m_Scene->GetPlayer();

				Vector2	Dir = Player->GetPos() - m_Pos;
				Dir.Normalize();

				if (Dir.x < 0)
				{
					m_Direction = true;
				}

				else
				{
					m_Direction = false;
				}

				m_AI = EMonsterAI::Attack;
			}
		}	

		m_RandActive = (float)(rand() % 3);
	}

	if (CheckCurrentAnimation("RightWillAttack1") || CheckCurrentAnimation("LeftWillAttack1"))
	{
		if (m_Direction)
		{
			SetOffset(-69.f, -17.f);
		}

		else
		{
			SetOffset(69.f, -20.f);
		}
	}

	else if (CheckCurrentAnimation("RightWillAttack2") || CheckCurrentAnimation("LeftWillAttack2"))
	{
		if (m_Direction)
		{
			SetOffset(-250.f, -15.f);
		}

		else
		{
			SetOffset(250.f, -15.f);
		}
	}

	else if (CheckCurrentAnimation("RightWillAttack3") || CheckCurrentAnimation("LeftWillAttack3"))
	{
		if (m_Direction)
		{
			SetOffset(205.f, 21.f);
		}

		else
		{
			SetOffset(-205.f, 21.f);
		}
	}

	else if (CheckCurrentAnimation("RightWillAttack4") || CheckCurrentAnimation("LeftWillAttack4"))
	{
		if (m_Direction)
		{
			SetOffset(-120.f, 40.f);
		}

		else
		{
			SetOffset(120.f, 40.f);
		}
	}

	else if (CheckCurrentAnimation("RightWillAttack5") || CheckCurrentAnimation("LeftWillAttack5"))
	{
		if (m_Direction)
		{
			SetOffset(-208.f, -8.f);
		}

		else
		{
			SetOffset(208.f, -8.f);
		}
	}

	else if (CheckCurrentAnimation("RightWillAttack6") || CheckCurrentAnimation("LeftWillAttack6"))
	{
		if (m_Direction)
		{
			SetOffset(189.f, 21.f);
		}

		else
		{
			SetOffset(-189.f, 21.f);
		}
	}

	else if (CheckCurrentAnimation("RightWillAttack7") || CheckCurrentAnimation("LeftWillAttack7"))
	{
		if (m_Direction)
		{
			SetOffset(-66.f, -74.f);
		}

		else
		{
			SetOffset(66.f, -74.f);
		}
	}

	else
	{
		SetOffset(0.f, 0.f);
	}

	switch (m_AI)
	{
	case EMonsterAI::Idle:
		AIIdle(DeltaTime);
		break;

	case EMonsterAI::Move:
		AIMove(DeltaTime);
		break;

	case EMonsterAI::Attack:
		AIAttack(DeltaTime);
		break;

	case EMonsterAI::Death:
		AIDeath(DeltaTime);
		break;
	}
}

void CWillPase2::PostUpdate(float DeltaTime)
{
	CMonster::PostUpdate(DeltaTime);
}

void CWillPase2::Collision(float DeltaTime)
{
	CMonster::Collision(DeltaTime);
}

void CWillPase2::Render(HDC hDC)
{
	CMonster::Render(hDC);
}

CWillPase2* CWillPase2::Clone()
{
	return new CWillPase2(*this);
}

float CWillPase2::SetDamage(float Damage)
{
	Damage = CCharacter::SetDamage(Damage);

	CUIBossWillPase2* State = m_Scene->FindUIWindow<CUIBossWillPase2>("WillStateHUD");

	if (State)
	{
		State->SetHPPercent1(m_CharacterInfo.HP / (float)m_CharacterInfo.HPMax);
	}

	return Damage;
}

void CWillPase2::AIIdle(float DeltaTime)
{
	CMonster::AIIdle(DeltaTime);

	if (CheckCurrentAnimation("LeftWillMove"))
	{
		ChangeAnimation("LeftWill");
	}

	if (CheckCurrentAnimation("RightWillMove"))
	{
		ChangeAnimation("RightWill");
	}
}

void CWillPase2::AIMove(float DeltaTime)
{
	CMonster::AIMove(DeltaTime);

	if (m_Direction)
	{
		ChangeAnimation("LeftWillMove");

		Move(Vector2(-1.f, 0), m_MoveSpeed);
	}

	else
	{
		ChangeAnimation("RightWillMove");

		Move(Vector2(1.f, 0), m_MoveSpeed);
	}
}

void CWillPase2::AIAttack(float DeltaTime)
{
	CMonster::AIAttack(DeltaTime);

	int Rand = rand() % 7 + 1;

	if (!m_IsAttackAni && m_IsAttack)
	{
		m_IsAttackAni = true;

		CGameObject* Player = m_Scene->GetPlayer();

		Vector2	Dir = Player->GetPos() - m_Pos;
		Dir.Normalize();

		if (Dir.x < 0)
		{
			m_Direction = true;
		}

		else
		{
			m_Direction = false;
		}

		if (m_Direction)
		{
			std::string AniName = "LeftWillAttack" + std::to_string(Rand);

			ChangeAnimation(AniName);
		}

		else
		{
			std::string AniName = "RightWillAttack" + std::to_string(Rand);

			ChangeAnimation(AniName);
		}
	}
}

void CWillPase2::AIDeath(float DeltaTime)
{
	CMonster::AIDeath(DeltaTime);
}

void CWillPase2::CollisionAttackBegin(CCollider* Src, CCollider* Dest, float DeltaTime)
{
	if (Dest->GetOwner()->GetName() == "Player")
	{
		m_IsAttack = true;
	}
}

void CWillPase2::CollisionAttackEnd(CCollider* Src, CCollider* Dest, float DeltaTime)
{
	if (Dest->GetOwner()->GetName() == "Player")
	{
		m_IsAttack = false;
	}
}

void CWillPase2::AttackAnimationStart()
{
	
}

void CWillPase2::AttackAnimationEnd()
{

}

void CWillPase2::AttackStart()
{
	m_IsAttackAni = true;
}

void CWillPase2::AttackEnd()
{
	m_IsAttackAni = false;

	if (m_Direction)
	{
		ChangeAnimation("LeftWill");
	}

	else
	{
		ChangeAnimation("RightWill");
	}

	/*if (!m_IsAttack)
	{
		
	}*/

	/*else
	{
		int Rand = rand() % 7 + 1;

		CGameObject* Player = m_Scene->GetPlayer();

		Vector2	Dir = Player->GetPos() - m_Pos;
		Dir.Normalize();

		if (Dir.x < 0)
		{
			m_Direction = true;
		}

		else
		{
			m_Direction = false;
		}

		if (m_Direction)
		{
			std::string AniName = "LeftWillAttack" + std::to_string(Rand);

			ChangeAnimation(AniName);
		}

		else
		{
			std::string AniName = "RightWillAttack" + std::to_string(Rand);

			ChangeAnimation(AniName);
		}
	}*/
}
