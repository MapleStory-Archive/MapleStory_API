#include "BossWillPase2.h"
#include "../GameManager.h"
#include "../Object/Player.h"
#include "../Object/PhantomBlow.h"
#include "../Object/BladeFury.h"
#include "../Object/ShadowBlade.h"
#include "../Object/WillPase2.h"
#include "../Object/UpSpiderLeg.h"
#include "../Object/DownSpiderLeg.h"
#include "../Object/Crack.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../UI/UITutorial.h"
#include "../UI/UICharacterStateHUD.h"
#include "../UI/UIBossWillPase2.h"
#include "../UI/UINotice.h"
#include "../Map/ScrollMap.h"
#include "../Map/TileMap.h"

CBossWillPase2::CBossWillPase2() : m_UpLegActive(false), m_DownLegActive(false), m_CrackActive(false), m_Time(5.f)
{
}

CBossWillPase2::~CBossWillPase2()
{
	m_vecLeg.clear();
}

bool CBossWillPase2::Init()
{
	LoadAnimationSequence();

	LoadSound();

	float Pos = 70.f;

	for (int i = 0; i * Pos < 1500; i++)
	{
		m_vecLeg.push_back(Pos * (float)i);
	}

	GetCamera()->SetWorldResolution(1500.f, 770.f);

	RECT rc = { 0, 0, 1366, 768 };

	HWND hWnd = CGameManager::GetInst()->GetWindowHandle();

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	SetWindowPos(hWnd, HWND_TOPMOST, 1920, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE);

	ShowWindow(hWnd, SW_SHOW);

	UpdateWindow(hWnd);

	CUpSpiderLeg* UpSpiderLeg = CreatePrototype<CUpSpiderLeg>("UpSpiderLeg");
	CDownSpiderLeg* DownSpiderLeg = CreatePrototype<CDownSpiderLeg>("DownSpiderLeg");

	CPhantomBlow* RightPhantomBlow = CreatePrototype<CPhantomBlow>("RightPhantomBlow", false);
	CPhantomBlow* LeftPhantomBlow = CreatePrototype<CPhantomBlow>("LeftPhantomBlow", true);

	CBladeFury* BladeFury = CreatePrototype<CBladeFury>("BladeFury", false);

	CPlayer* Player = CreateObject<CPlayer>("Player");

	SetPlayer(Player);

	GetCamera()->SetTarget(Player);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	CScrollMap* Map = CreateMap<CScrollMap>("BossWillPase2");
	Map->SetSize(1500.f, 770.f);
	Map->SetTexture("BossWillPase2", TEXT("BossWIllPase2.bmp"));
	Map->SetLoop(false);
	Map->SetScrollRatio(1.0f, 1.0f);
	Map->SetZOrder(0);

	Player->SetRange(1500.f, 770.f);

	CWillPase2* Will = CreateObject<CWillPase2>("Monster", Vector2(750.f, 445.f));

	CTileMap* TileMap = CreateMap<CTileMap>("BossWillPase2", Vector2(0.f, 0.f), Vector2(1500.f, 770.f));

	TileMap->LoadFile("BossWillPase2");
	TileMap->SetZOrder(2);

	Player->SetRange(1500.f, 770.f);
	Will->SetRange(1500.f, 770.f);

	CUITutorial* TutorialWindow = CreateUIWindow<CUITutorial>("BossWillPase2");

	CUICharacterStateHUD* StateWindow = CreateUIWindow<CUICharacterStateHUD>("CharacterStateHUD");
	CUIBossWillPase2* WillWindow = CreateUIWindow<CUIBossWillPase2>("WillStateHUD");

	return true;
}

bool CBossWillPase2::Update(float DeltaTime)
{
	CScene::Update(DeltaTime);

	CWillPase2* Will = (CWillPase2*)FindObject("Monster");

	if (Will->GetCharacterInfo().HP <= 0)
	{
		if (!FindObject("Crack"))
		{
			CCrack* Crack = CreateObject<CCrack>("Crack", Vector2(0.f, 392.f));
			CUINotice* Notice = CreateUIWindow<CUINotice>("Notice");
		}	
	}

	else
	{
		m_Time -= DeltaTime;

		if (m_Time <= 0 && !m_UpLegActive)
		{
			m_UpLegActive = true;

			m_Time = 2.5f;

			for (int i = 0; i < 7; i++)
			{
				int IsUpDown = rand() % 2;

				int RandPosX = rand() % m_vecLeg.size();

				if (IsUpDown == 1)
				{
					CDownSpiderLeg* UpLeg = CreateObject<CDownSpiderLeg>("DownSpiderLeg", "DownSpiderLeg", Vector2(m_vecLeg[RandPosX], 1200.f));
				}

				else
				{
					CUpSpiderLeg* UpLeg = CreateObject<CUpSpiderLeg>("UpSpiderLeg", "UpSpiderLeg", Vector2(m_vecLeg[RandPosX], -250.f));
				}
			}
		}
	}

	if (m_UpLegActive && m_Time <= 0)
	{
		m_Time = 3.f;

		m_UpLegActive = false;
	}

	return true;
}

bool CBossWillPase2::PostUpdate(float DeltaTime)
{
	CScene::PostUpdate(DeltaTime);

	return true;
}

bool CBossWillPase2::Collision(float DeltaTime)
{
	CScene::Collision(DeltaTime);

	return true;
}

bool CBossWillPase2::Render(HDC hDC)
{
	CScene::Render(hDC);

	return true;
}

void CBossWillPase2::LoadAnimationSequence()
{
	// Player
	GetSceneResource()->CreateAnimationSequence("PlayerRightIdle", "PlayerRightIdle", TEXT("Player/R/stand.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerRightIdle", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerLeftIdle", "PlayerLeftIdle", TEXT("Player/L/stand.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerLeftIdle", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerLeftWalk", "PlayerLeftWalk", TEXT("Player/L/walk.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerLeftWalk", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerRightWalk", "PlayerRightWalk", TEXT("Player/R/walk.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerRightWalk", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerLeftAttack", "PlayerLeftAttack", TEXT("Player/L/stabD1.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerLeftAttack", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerRightAttack", "PlayerRightAttack", TEXT("Player/R/stabD1.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerRightAttack", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerLeftPhantomBlow", "PlayerLeftPhantomBlow", TEXT("Player/L/phantomBlow.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerLeftPhantomBlow", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerRightPhantomBlow", "PlayerRightPhantomBlow", TEXT("Player/R/phatomBlow.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerRightPhantomBlow", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerRightBladeFury", "PlayerRightBladeFury", TEXT("Player/R/BladeFury.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerRightBladeFury", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerLeftBladeFury", "PlayerLeftBladeFury", TEXT("Player/L/bladeFury.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerLeftBladeFury", 255, 0, 255);

	// Player 이펙트
	GetSceneResource()->CreateAnimationSequence("RightPhantomBlow", "RightPhantomBlow", TEXT("Player/Effect/R/PhantomBlow.bmp"));

	GetSceneResource()->SetTextureColorKey("RightPhantomBlow", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("LeftPhantomBlow", "LeftPhantomBlow", TEXT("Player/Effect/L/PhantomBlow.bmp"));

	GetSceneResource()->SetTextureColorKey("LeftPhantomBlow", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("BladeFury", "BladeFury", TEXT("Player/Effect/BladeFury.bmp"));

	GetSceneResource()->SetTextureColorKey("BladeFury", 255, 0, 255);

	//보스 몬스터
	GetSceneResource()->CreateAnimationSequence("RightWill", "RightWill", TEXT("Will/2/stand/R/Stand.bmp"));

	GetSceneResource()->SetTextureColorKey("RightWill", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("LeftWill", "LeftWill", TEXT("Will/2/stand/L/Stand.bmp"));

	GetSceneResource()->SetTextureColorKey("LeftWill", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("RightWillMove", "RightWillMove", TEXT("Will/2/move/R/Move.bmp"));

	GetSceneResource()->SetTextureColorKey("RightWillMove", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("LeftWillMove", "LeftWillMove", TEXT("Will/2/move/L/Move.bmp"));

	GetSceneResource()->SetTextureColorKey("LeftWillMove", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("RightWillAttack1", "RightWillAttack1", TEXT("Will/2/attack1/R/attack1.bmp"));

	GetSceneResource()->SetTextureColorKey("RightWillAttack1", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("LeftWillAttack1", "LeftWillAttack1", TEXT("Will/2/attack1/L/attack1.bmp"));

	GetSceneResource()->SetTextureColorKey("LeftWillAttack1", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("RightWillAttack2", "RightWillAttack2", TEXT("Will/2/attack2/R/attack2.bmp"));

	GetSceneResource()->SetTextureColorKey("RightWillAttack2", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("LeftWillAttack2", "LeftWillAttack2", TEXT("Will/2/attack2/L/attack2.bmp"));

	GetSceneResource()->SetTextureColorKey("LeftWillAttack2", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("RightWillAttack3", "RightWillAttack3", TEXT("Will/2/attack3/R/attack3.bmp"));

	GetSceneResource()->SetTextureColorKey("RightWillAttack3", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("LeftWillAttack3", "LeftWillAttack3", TEXT("Will/2/attack3/L/attack3.bmp"));

	GetSceneResource()->SetTextureColorKey("LeftWillAttack3", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("RightWillAttack4", "RightWillAttack4", TEXT("Will/2/attack4/R/attack4.bmp"));

	GetSceneResource()->SetTextureColorKey("RightWillAttack4", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("LeftWillAttack4", "LeftWillAttack4", TEXT("Will/2/attack4/L/attack4.bmp"));

	GetSceneResource()->SetTextureColorKey("LeftWillAttack4", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("RightWillAttack5", "RightWillAttack5", TEXT("Will/2/attack5/R/attack5.bmp"));

	GetSceneResource()->SetTextureColorKey("RightWillAttack5", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("LeftWillAttack5", "LeftWillAttack5", TEXT("Will/2/attack5/L/attack5.bmp"));

	GetSceneResource()->SetTextureColorKey("LeftWillAttack5", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("RightWillAttack6", "RightWillAttack6", TEXT("Will/2/attack6/R/attack6.bmp"));

	GetSceneResource()->SetTextureColorKey("RightWillAttack6", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("LeftWillAttack6", "LeftWillAttack6", TEXT("Will/2/attack6/L/attack6.bmp"));

	GetSceneResource()->SetTextureColorKey("LeftWillAttack6", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("RightWillAttack7", "RightWillAttack7", TEXT("Will/2/attack7/R/attack7.bmp"));

	GetSceneResource()->SetTextureColorKey("RightWillAttack7", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("LeftWillAttack7", "LeftWillAttack7", TEXT("Will/2/attack7/L/attack7.bmp"));

	GetSceneResource()->SetTextureColorKey("LeftWillAttack7", 255, 0, 255);

	// 맵 패턴
	GetSceneResource()->CreateAnimationSequence("UpSpiderLeg", "UpSpiderLeg", TEXT("Will/2/Effect/level0_4.bmp"));

	GetSceneResource()->SetTextureColorKey("UpSpiderLeg", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("DownSpiderLeg", "DownSpiderLeg", TEXT("Will/2/Effect/Strip 4.bmp"));

	GetSceneResource()->SetTextureColorKey("DownSpiderLeg", 0, 0, 0);

	GetSceneResource()->CreateAnimationSequence("Crack", "Crack", TEXT("Will/2/Effect/tile.bmp"));

	GetSceneResource()->SetTextureColorKey("Crack", 255, 0, 255);
}

void CBossWillPase2::LoadSound()
{
}
