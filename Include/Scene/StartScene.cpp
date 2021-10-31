#include "StartScene.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../UI/UIStart.h"
#include "../GameManager.h"

CStartScene::CStartScene()
{
}

CStartScene::~CStartScene()
{
}

bool CStartScene::Init()
{
	LoadSound();

	LoadAnimationSequence();

	RECT rc = { 0, 0, 1024, 768 };

	HWND hWnd = CGameManager::GetInst()->GetWindowHandle();

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	SetWindowPos(hWnd, HWND_TOPMOST, 1920, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE);

	ShowWindow(hWnd, SW_SHOW);

	UpdateWindow(hWnd);

	CUIStart* StartWindow = CreateUIWindow<CUIStart>("StartWindow");

	return true;
}

void CStartScene::LoadAnimationSequence()
{
	// Player
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

	for (int i = 0; i < 6; i++)
	{
		GetSceneResource()->AddAnimationFrameData("RightShadowBladeMove", i * 64.f, 0.f, 64.f, 63.f);
	}

	GetSceneResource()->CreateAnimationSequence("LeftShadowBladeMove", "LeftShadowBladeMove", TEXT("Monster/ShadowBlade/Move/L/Move.bmp"));

	GetSceneResource()->SetTextureColorKey("LeftShadowBladeMove", 255, 0, 255);

	for (int i = 0; i < 6; i++)
	{
		GetSceneResource()->AddAnimationFrameData("LeftShadowBladeMove", i * 64.f, 0.f, 64.f, 63.f);
	}

	GetSceneResource()->CreateAnimationSequence("RightShadowBladeAttack", "RightShadowBladeAttack", TEXT("Monster/ShadowBlade/Attack/R/Attack.bmp"));

	GetSceneResource()->SetTextureColorKey("RightShadowBladeAttack", 255, 0, 255);

	for (int i = 0; i < 9; i++)
	{
		GetSceneResource()->AddAnimationFrameData("RightShadowBladeAttack", i * 153.f, 0.f, 153.f, 137.f);
	}

	GetSceneResource()->CreateAnimationSequence("LeftShadowBladeAttack", "LeftShadowBladeAttack", TEXT("Monster/ShadowBlade/Attack/L/Attack.bmp"));

	GetSceneResource()->SetTextureColorKey("LeftShadowBladeAttack", 255, 0, 255);

	for (int i = 0; i < 9; i++)
	{
		GetSceneResource()->AddAnimationFrameData("LeftShadowBladeAttack", i * 153.f, 0.f, 153.f, 137.f);
	}

	// 포탈
	GetSceneResource()->CreateAnimationSequence("Potal", "Potal", TEXT("Potal.bmp"));

	GetSceneResource()->SetTextureColorKey("Potal", 255, 0, 255);

	for (int i = 0; i < 8; i++)
	{
		GetSceneResource()->AddAnimationFrameData("Potal", i * 104.f, 0.f, 104.f, 142.f);
	}

	//보스 몬스터
	GetSceneResource()->CreateAnimationSequence("RightWill", "RightWill", TEXT("Will/2/stand/R/Stand.bmp"));

	GetSceneResource()->SetTextureColorKey("RightWill", 255, 0, 255);

	for (int i = 0; i < 16; i++)
	{
		GetSceneResource()->AddAnimationFrameData("RightWill", i * 203.f, 0.f, 203.f, 365.f);
	}

	GetSceneResource()->CreateAnimationSequence("LeftWill", "LeftWill", TEXT("Will/2/stand/L/Stand.bmp"));

	GetSceneResource()->SetTextureColorKey("LeftWill", 255, 0, 255);

	for (int i = 0; i < 16; i++)
	{
		GetSceneResource()->AddAnimationFrameData("LeftWill", i * 203.f, 0.f, 203.f, 365.f);
	}

	GetSceneResource()->CreateAnimationSequence("RightWillMove", "RightWillMove", TEXT("Will/2/move/R/Move.bmp"));

	GetSceneResource()->SetTextureColorKey("RightWillMove", 255, 0, 255);

	for (int i = 0; i < 16; i++)
	{
		GetSceneResource()->AddAnimationFrameData("RightWillMove", i * 203.f, 0.f, 203.f, 364.f);
	}

	GetSceneResource()->CreateAnimationSequence("LeftWillMove", "LeftWillMove", TEXT("Will/2/move/L/Move.bmp"));

	GetSceneResource()->SetTextureColorKey("LeftWillMove", 255, 0, 255);

	for (int i = 0; i < 16; i++)
	{
		GetSceneResource()->AddAnimationFrameData("LeftWillMove", i * 203.f, 0.f, 203.f, 364.f);
	}

	GetSceneResource()->CreateAnimationSequence("RightWillAttack1", "RightWillAttack1", TEXT("Will/2/attack1/R/attack1.bmp"));

	GetSceneResource()->SetTextureColorKey("RightWillAttack1", 255, 0, 255);

	for (int i = 0; i < 20; i++)
	{
		GetSceneResource()->AddAnimationFrameData("RightWillAttack1", i * 593.f, 0.f, 593.f, 534.f);
	}

	GetSceneResource()->CreateAnimationSequence("LeftWillAttack1", "LeftWillAttack1", TEXT("Will/2/attack1/L/attack1.bmp"));

	GetSceneResource()->SetTextureColorKey("LeftWillAttack1", 255, 0, 255);

	for (int i = 0; i < 20; i++)
	{
		GetSceneResource()->AddAnimationFrameData("LeftWillAttack1", i * 593.f, 0.f, 593.f, 534.f);
	}

	GetSceneResource()->CreateAnimationSequence("RightWillAttack2", "RightWillAttack2", TEXT("Will/2/attack2/R/attack2.bmp"));

	GetSceneResource()->SetTextureColorKey("RightWillAttack2", 255, 0, 255);

	for (int i = 0; i < 20; i++)
	{
		GetSceneResource()->AddAnimationFrameData("RightWillAttack2", i * 728.f, 0.f, 728.f, 516.f);
	}

	GetSceneResource()->CreateAnimationSequence("LeftWillAttack2", "LeftWillAttack2", TEXT("Will/2/attack2/L/attack2.bmp"));

	GetSceneResource()->SetTextureColorKey("LeftWillAttack2", 255, 0, 255);

	for (int i = 0; i < 20; i++)
	{
		GetSceneResource()->AddAnimationFrameData("LeftWillAttack2", i * 728.f, 0.f, 728.f, 516.f);
	}

	GetSceneResource()->CreateAnimationSequence("RightWillAttack3", "RightWillAttack3", TEXT("Will/2/attack3/R/attack3.bmp"));

	GetSceneResource()->SetTextureColorKey("RightWillAttack3", 255, 0, 255);

	for (int i = 0; i < 20; i++)
	{
		GetSceneResource()->AddAnimationFrameData("RightWillAttack3", i * 860.f, 0.f, 860.f, 444.f);
	}

	GetSceneResource()->CreateAnimationSequence("LeftWillAttack3", "LeftWillAttack3", TEXT("Will/2/attack3/L/attack3.bmp"));

	GetSceneResource()->SetTextureColorKey("LeftWillAttack3", 255, 0, 255);

	for (int i = 0; i < 20; i++)
	{
		GetSceneResource()->AddAnimationFrameData("LeftWillAttack3", i * 860.f, 0.f, 860.f, 444.f);
	}

	GetSceneResource()->CreateAnimationSequence("RightWillAttack4", "RightWillAttack4", TEXT("Will/2/attack4/R/attack4.bmp"));

	GetSceneResource()->SetTextureColorKey("RightWillAttack4", 255, 0, 255);

	for (int i = 0; i < 30; i++)
	{
		GetSceneResource()->AddAnimationFrameData("RightWillAttack4", i * 622.f, 0.f, 622.f, 589.f);
	}

	GetSceneResource()->CreateAnimationSequence("LeftWillAttack4", "LeftWillAttack4", TEXT("Will/2/attack4/L/attack4.bmp"));

	GetSceneResource()->SetTextureColorKey("LeftWillAttack4", 255, 0, 255);

	for (int i = 0; i < 30; i++)
	{
		GetSceneResource()->AddAnimationFrameData("LeftWillAttack4", i * 622.f, 0.f, 622.f, 589.f);
	}

	GetSceneResource()->CreateAnimationSequence("RightWillAttack5", "RightWillAttack5", TEXT("Will/2/attack5/R/attack5.bmp"));

	GetSceneResource()->SetTextureColorKey("RightWillAttack5", 255, 0, 255);

	for (int i = 0; i < 20; i++)
	{
		GetSceneResource()->AddAnimationFrameData("RightWillAttack5", i * 665.f, 0.f, 655.f, 499.f);
	}

	GetSceneResource()->CreateAnimationSequence("LeftWillAttack5", "LeftWillAttack5", TEXT("Will/2/attack5/L/attack5.bmp"));

	GetSceneResource()->SetTextureColorKey("LeftWillAttack5", 255, 0, 255);

	for (int i = 0; i < 20; i++)
	{
		GetSceneResource()->AddAnimationFrameData("LeftWillAttack5", i * 665.f, 0.f, 655.f, 499.f);
	}

	GetSceneResource()->CreateAnimationSequence("RightWillAttack6", "RightWillAttack6", TEXT("Will/2/attack6/R/attack6.bmp"));

	GetSceneResource()->SetTextureColorKey("RightWillAttack6", 255, 0, 255);

	for (int i = 0; i < 20; i++)
	{
		GetSceneResource()->AddAnimationFrameData("RightWillAttack6", i * 701.f, 0.f, 701.f, 442.f);
	}

	GetSceneResource()->CreateAnimationSequence("LeftWillAttack6", "LeftWillAttack6", TEXT("Will/2/attack6/L/attack6.bmp"));

	GetSceneResource()->SetTextureColorKey("LeftWillAttack6", 255, 0, 255);

	for (int i = 0; i < 20; i++)
	{
		GetSceneResource()->AddAnimationFrameData("LeftWillAttack6", i * 701.f, 0.f, 701.f, 442.f);
	}

	GetSceneResource()->CreateAnimationSequence("RightWillAttack7", "RightWillAttack7", TEXT("Will/2/attack7/R/attack7.bmp"));

	GetSceneResource()->SetTextureColorKey("RightWillAttack7", 255, 0, 255);

	for (int i = 0; i < 16; i++)
	{
		GetSceneResource()->AddAnimationFrameData("RightWillAttack7", i * 334.f, 0.f, 334.f, 513.f);
	}

	GetSceneResource()->CreateAnimationSequence("LeftWillAttack7", "LeftWillAttack7", TEXT("Will/2/attack7/L/attack7.bmp"));

	GetSceneResource()->SetTextureColorKey("LeftWillAttack7", 255, 0, 255);

	for (int i = 0; i < 16; i++)
	{
		GetSceneResource()->AddAnimationFrameData("LeftWillAttack7", i * 334.f, 0.f, 334.f, 513.f);
	}

	// 맵 패턴
	GetSceneResource()->CreateAnimationSequence("UpSpiderLeg", "UpSpiderLeg", TEXT("Will/2/Effect/level0_4.bmp"));

	GetSceneResource()->SetTextureColorKey("UpSpiderLeg", 255, 0, 255);

	for (int i = 0; i < 30; i++)
	{
		GetSceneResource()->AddAnimationFrameData("UpSpiderLeg", i * 680.f, 0.f, 680.f, 720.f);
	}

	GetSceneResource()->CreateAnimationSequence("DownSpiderLeg", "DownSpiderLeg", TEXT("Will/2/Effect/Strip 4.bmp"));

	GetSceneResource()->SetTextureColorKey("DownSpiderLeg", 0, 0, 0);

	for (int i = 0; i < 30; i++)
	{
		GetSceneResource()->AddAnimationFrameData("DownSpiderLeg", i * 608.f, 0.f, 608.f, 744.f);
	}

	GetSceneResource()->CreateAnimationSequence("Crack", "Crack", TEXT("Will/2/Effect/tile.bmp"));

	GetSceneResource()->SetTextureColorKey("Crack", 255, 0, 255);

	for (int i = 0; i < 8; i++)
	{
		GetSceneResource()->AddAnimationFrameData("Crack", i * 1425.f, 0.f, 1425.f, 392.f);
	}
}

void CStartScene::LoadSound()
{
	GetSceneResource()->LoadSound("BGM", true, "BGM", "secretFlower.mp3");
	GetSceneResource()->SoundPlay("BGM");
}
