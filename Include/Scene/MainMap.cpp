#include "MainMap.h"
#include "TutorialMap.h"
#include "../GameManager.h"
#include "../Object/GameObjectManager.h"
#include "../Object/Player.h"
#include "../Object/PhantomBlow.h"
#include "../Object/BladeFury.h"
#include "../Object/Potal.h"
#include "SceneResource.h"
#include "SceneManager.h"
#include "Camera.h"
#include "../UI/UITutorial.h"
#include "../UI/UICharacterStateHUD.h"
#include "../Map/ScrollMap.h"
#include "../Map/TileMap.h"

CMainMap::CMainMap()
{
}

CMainMap::~CMainMap()
{
}

bool CMainMap::Init()
{
	LoadAnimationSequence();

	LoadSound();

	GetCamera()->SetWorldResolution(1785.f, 1197.f);

	CPlayer* Player = CreateObject<CPlayer>("Player");

	CGameObjectManager::GetInst()->PassPlayer(Player);

	SetPlayer(Player);

	GetCamera()->SetTarget(Player);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	CScrollMap* Map = CreateMap<CScrollMap>("MainMap");
	Map->SetSize(1785.f, 1197.f);
	Map->SetTexture("MainMap", TEXT("MainScene.bmp"));
	Map->SetLoop(false);
	Map->SetScrollRatio(1.0f, 1.0f);
	Map->SetZOrder(0);

	Player->SetRange(1785.f, 1197.f);

	CTileMap* TileMap = CreateMap<CTileMap>("MainMap", Vector2(0.f, 0.f), Vector2(1785.f, 1200.f));

	TileMap->LoadFile("MainMap");
	TileMap->SetZOrder(2);

	CUICharacterStateHUD* StateWindow = CreateUIWindow<CUICharacterStateHUD>("CharacterStateHUD");

	return true;
}

void CMainMap::LoadAnimationSequence()
{
	// Player 애니메이션
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

}

void CMainMap::LoadSound()
{
}
