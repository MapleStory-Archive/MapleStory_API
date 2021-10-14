#include "TutorialMap.h"
#include "../GameManager.h"
#include "../Object/Player.h"
#include "../Object/PhantomBlow.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../UI/UIMain.h"
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

	CPlayer* Player = CreateObject<CPlayer>("Player");

	SetPlayer(Player);


	GetCamera()->SetTarget(Player);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	CScrollMap* Map = CreateMap<CScrollMap>("ScrollMap");
	Map->SetSize(1500.f, 770.f);
	Map->SetTexture("ScrollBack", TEXT("20210928211449847_103050530.bmp"));
	Map->SetLoop(false);
	Map->SetScrollRatio(1.0f, 1.0f);
	Map->SetZOrder(0);

	CTileMap* TileMap = CreateMap<CTileMap>("TutorialMap", Vector2(0.f, 0.f), Vector2(1500.f, 770.f));

	TileMap->LoadFile("TutorialMap");
	TileMap->SetZOrder(2);

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

	// Player 이펙트
	GetSceneResource()->CreateAnimationSequence("RightPhantomBlow", "RightPhantomBlow", TEXT("Player/R/Effect/PhantomBlow.bmp"));

	GetSceneResource()->SetTextureColorKey("RightPhantomBlow", 255, 0, 255);

	for (int i = 0; i < 10; i++)
	{
		GetSceneResource()->AddAnimationFrameData("RightPhantomBlow", i * 412.f, 0.f, 412.f, 210.f);
	}

	GetSceneResource()->CreateAnimationSequence("LeftPhantomBlow", "LeftPhantomBlow", TEXT("Player/L/Effect/PhantomBlow.bmp"));

	GetSceneResource()->SetTextureColorKey("LeftPhantomBlow", 255, 0, 255);

	for (int i = 0; i < 10; i++)
	{
		GetSceneResource()->AddAnimationFrameData("LeftPhantomBlow", i * 412.f, 0.f, 412.f, 210.f);
	}
}

void CTutorialMap::LoadSound()
{
}
