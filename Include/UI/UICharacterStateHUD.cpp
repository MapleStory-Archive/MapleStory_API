#include "UICharacterStateHUD.h"
#include "../GameManager.h"
#include "../Scene/MainScene.h"
#include "../Scene/SceneManager.h"

CUICharacterStateHUD::CUICharacterStateHUD()
{
}

CUICharacterStateHUD::~CUICharacterStateHUD()
{
}

bool CUICharacterStateHUD::Init()
{
	SetPos(30.f, 20.f);

	Resolution	RS = CGameManager::GetInst()->GetResolution();

	CUIImage* Back = CreateWidget<CUIImage>("HPBarBack");

	Back->SetTexture("BarBack", TEXT("BarBack.bmp"));
	Back->SetTextureColorKey(255, 0, 255);

	//Back->SetPos(30.f, 20.f);

	m_HPBar = CreateWidget<CProgressBar>("HPBar");

	m_HPBar->SetTexture("HPBar", TEXT("BarDefault.bmp"));

	m_HPBar->SetPos(10.f, 10.f);

	Back = CreateWidget<CUIImage>("MPBarBack");

	Back->SetTexture("BarBack", TEXT("BarBack.bmp"));

	Back->SetPos(0.f, 40.f);
	Back->SetTextureColorKey(255, 0, 255);

	//Back->SetPos(30.f, 20.f);

	m_MPBar = CreateWidget<CProgressBar>("MPBar");

	m_MPBar->SetTexture("MPBar", TEXT("BarDefault1.bmp"));

	m_MPBar->SetPos(10.f, 50.f);

	return true;
}