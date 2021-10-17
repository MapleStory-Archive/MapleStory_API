#include "TutorialMap.h"
#include "../GameManager.h"
#include "../Object/Player.h"
#include "../Object/PhantomBlow.h"
#include "../Object/BladeFury.h"
#include "../Object/ShadowBlade.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../UI/UITutorial.h"
#include "../UI/UICharacterStateHUD.h"
#include "../Map/ScrollMap.h"
#include "../Map/TileMap.h"

CTutorialMap::CTutorialMap()
{
}

CTutorialMap::~CTutorialMap()
{
}

bool CTutorialMap::Init()
{
	LoadAnimationSequence();

	LoadSound();

	GetCamera()->SetWorldResolution(1500.f, 770.f);

	RECT rc = { 0, 0, 1366, 768 };

	HWND hWnd = CGameManager::GetInst()->GetWindowHandle();

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	SetWindowPos(hWnd, HWND_TOPMOST, 1920, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE);

	ShowWindow(hWnd, SW_SHOW);

	UpdateWindow(hWnd);

	CPhantomBlow* RightPhantomBlow = CreatePrototype<CPhantomBlow>("RightPhantomBlow", false);
	CPhantomBlow* LeftPhantomBlow = CreatePrototype<CPhantomBlow>("LeftPhantomBlow", true);

	CBladeFury* BladeFury = CreatePrototype<CBladeFury>("BladeFury", false);

	CPlayer* Player = CreateObject<CPlayer>("Player", Vector2(100.f, 650.f));

	SetPlayer(Player);

	GetCamera()->SetTarget(Player);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	CShadowBlade* ShadowBlade = CreateObject<CShadowBlade>("ShadowBlade", Vector2(1000.f, 650.f));

	CScrollMap* Map = CreateMap<CScrollMap>("ScrollMap");
	Map->SetSize(1500.f, 770.f);
	Map->SetTexture("ScrollBack", TEXT("20210928211449847_103050530.bmp"));
	Map->SetLoop(false);
	Map->SetScrollRatio(1.0f, 1.0f);
	Map->SetZOrder(0);

	Player->SetRange(1500.f, 770.f);
	ShadowBlade->SetRange(1500.f, 770.f);

	CTileMap* TileMap = CreateMap<CTileMap>("TutorialMap", Vector2(0.f, 0.f), Vector2(1500.f, 770.f));

	TileMap->LoadFile("TutorialMap");
	TileMap->SetZOrder(2);

	CUITutorial* TutorialWindow = CreateUIWindow<CUITutorial>("TutorialWindow");

	CUICharacterStateHUD* StateWindow = CreateUIWindow<CUICharacterStateHUD>("CharacterStateHUD");

	return true;
}

void CTutorialMap::LoadAnimationSequence()
{
	// Player 애니메이션
	GetSceneResource()->CreateAnimationSequence("PlayerRightIdle", "PlayerRightIdle", TEXT("Player/R/stand.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerRightIdle", 255, 0, 255);

	for (int i = 0; i < 3; i++)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerRightIdle", i * 72.f, 0.f, 72.f, 71.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerLeftIdle", "PlayerLeftIdle", TEXT("Player/L/stand.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerLeftIdle", 255, 0, 255);

	for (int i = 0; i < 3; i++)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerLeftIdle", i * 72.f, 0.f, 72.f, 71.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerLeftWalk", "PlayerLeftWalk", TEXT("Player/L/walk.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerLeftWalk", 255, 0, 255);

	for (int i = 0; i < 4; i++)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerLeftWalk", i * 75.f, 0.f, 75.f, 71.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerRightWalk", "PlayerRightWalk", TEXT("Player/R/walk.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerRightWalk", 255, 0, 255);

	for (int i = 0; i < 4; i++)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerRightWalk", i * 75.f, 0.f, 75.f, 71.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerLeftAttack", "PlayerLeftAttack", TEXT("Player/L/stabD1.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerLeftAttack", 255, 0, 255);

	for (int i = 0; i < 4; i++)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerLeftAttack", i * 107.f, 0.f, 107.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerRightAttack", "PlayerRightAttack", TEXT("Player/R/stabD1.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerRightAttack", 255, 0, 255);

	for (int i = 0; i < 4; i++)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerRightAttack", i * 107.f, 0.f, 107.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerLeftPhantomBlow", "PlayerLeftPhantomBlow", TEXT("Player/L/phantomBlow.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerLeftPhantomBlow", 255, 0, 255);

	for (int i = 0; i < 9; i++)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerLeftPhantomBlow", i * 114.f, 0.f, 114.f, 81.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerRightPhantomBlow", "PlayerRightPhantomBlow", TEXT("Player/R/phatomBlow.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerRightPhantomBlow", 255, 0, 255);

	for (int i = 0; i < 9; i++)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerRightPhantomBlow", i * 114.f, 0.f, 114.f, 81.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerRightBladeFury", "PlayerRightBladeFury", TEXT("Player/R/BladeFury.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerRightBladeFury", 255, 0, 255);

	for (int i = 0; i < 10; i++)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerRightBladeFury", i * 109.f, 0.f, 109.f, 161.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerLeftBladeFury", "PlayerLeftBladeFury", TEXT("Player/L/bladeFury.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerLeftBladeFury", 255, 0, 255);

	for (int i = 0; i < 10; i++)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerLeftBladeFury", i * 109.f, 0.f, 109.f, 161.f);
	}

	// Player 이펙트
	GetSceneResource()->CreateAnimationSequence("RightPhantomBlow", "RightPhantomBlow", TEXT("Player/Effect/R/PhantomBlow.bmp"));

	GetSceneResource()->SetTextureColorKey("RightPhantomBlow", 255, 0, 255);

	for (int i = 0; i < 10; i++)
	{
		GetSceneResource()->AddAnimationFrameData("RightPhantomBlow", i * 412.f, 0.f, 412.f, 210.f);
	}

	GetSceneResource()->CreateAnimationSequence("LeftPhantomBlow", "LeftPhantomBlow", TEXT("Player/Effect/L/PhantomBlow.bmp"));

	GetSceneResource()->SetTextureColorKey("LeftPhantomBlow", 255, 0, 255);

	for (int i = 0; i < 10; i++)
	{
		GetSceneResource()->AddAnimationFrameData("LeftPhantomBlow", i * 412.f, 0.f, 412.f, 210.f);
	}

	GetSceneResource()->CreateAnimationSequence("BladeFury", "BladeFury", TEXT("Player/Effect/BladeFury.bmp"));

	GetSceneResource()->SetTextureColorKey("BladeFury", 255, 0, 255);

	for (int i = 0; i < 8; i++)
	{
		GetSceneResource()->AddAnimationFrameData("BladeFury", i * 469.f, 0.f, 469.f, 195.f);
	}

	// Monster 애니메이션
	GetSceneResource()->CreateAnimationSequence("RightShadowBladeStand", "RightShadowBladeStand", TEXT("Monster/ShadowBlade/Stand/R/Stand.bmp"));

	GetSceneResource()->SetTextureColorKey("RightShadowBladeStand", 255, 0, 255);

	for (int i = 0; i < 4; i++)
	{
		GetSceneResource()->AddAnimationFrameData("RightShadowBladeStand", i * 65.f, 0.f, 65.f, 67.f);
	}

	GetSceneResource()->CreateAnimationSequence("LeftShadowBladeStand", "LeftShadowBladeStand", TEXT("Monster/ShadowBlade/Stand/L/Stand.bmp"));

	GetSceneResource()->SetTextureColorKey("LeftShadowBladeStand", 255, 0, 255);

	for (int i = 0; i < 4; i++)
	{
		GetSceneResource()->AddAnimationFrameData("LeftShadowBladeStand", i * 65.f, 0.f, 65.f, 67.f);
	}

	GetSceneResource()->CreateAnimationSequence("RightShadowBladeMove", "RightShadowBladeMove", TEXT("Monster/ShadowBlade/Move/R/Move.bmp"));

	GetSceneResource()->SetTextureColorKey("RightShadowBladeMove", 255, 0, 255);

	for (int i = 0; i < 4; i++)
	{
		GetSceneResource()->AddAnimationFrameData("RightShadowBladeMove", i * 65.f, 0.f, 65.f, 67.f);
	}

	GetSceneResource()->CreateAnimationSequence("LeftShadowBladeMove", "LeftShadowBladeMove", TEXT("Monster/ShadowBlade/Move/L/Move.bmp"));

	GetSceneResource()->SetTextureColorKey("LeftShadowBladeMove", 255, 0, 255);

	for (int i = 0; i < 4; i++)
	{
		GetSceneResource()->AddAnimationFrameData("LeftShadowBladeMove", i * 65.f, 0.f, 65.f, 67.f);
	}
}

void CTutorialMap::LoadSound()
{
}
