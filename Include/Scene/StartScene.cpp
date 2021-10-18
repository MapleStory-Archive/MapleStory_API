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
	
}

void CStartScene::LoadSound()
{
	GetSceneResource()->LoadSound("BGM", true, "BGM", "secretFlower.mp3");
	GetSceneResource()->SoundPlay("BGM");
}
