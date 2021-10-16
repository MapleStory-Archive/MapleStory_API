#include "UICharacterStateHUD.h"
#include "../GameManager.h"
#include "../Scene/SceneManager.h"

CUICharacterStateHUD::CUICharacterStateHUD()
{
}

CUICharacterStateHUD::~CUICharacterStateHUD()
{
}

bool CUICharacterStateHUD::Init()
{
	Resolution	RS = CGameManager::GetInst()->GetResolution();

	SetPos(RS.Width / 2.f - 102.f, RS.Height - 85.f);

	CUIImage* Back = CreateWidget<CUIImage>("StatusBar");

	Back->SetTexture("StatusBar", TEXT("StatusBar.bmp"));
	Back->SetTextureColorKey(0, 0, 0);
	Back->SetZOrder(3);

	Back = CreateWidget<CUIImage>("backgrnd");

	Back->SetTexture("backgrnd", TEXT("status.backgrnd.bmp"));
	Back->SetTextureColorKey(0, 0, 0);
	Back->SetPos(3.f, 25.f);
	Back->SetZOrder(1);

	m_HPBar = CreateWidget<CProgressBar>("HPBar");

	m_HPBar->SetTexture("HPBar", TEXT("status.gauge.hp.layer.bmp"));

	m_HPBar->SetPos(25.f, 28.f);
	m_HPBar->SetZOrder(2);

	m_MPBar = CreateWidget<CProgressBar>("MPBar");

	m_MPBar->SetTexture("MPBar", TEXT("status.gauge.mp.layer.bmp"));

	m_MPBar->SetPos(25.f, 44.f);
	m_MPBar->SetZOrder(2);

	return true;
}