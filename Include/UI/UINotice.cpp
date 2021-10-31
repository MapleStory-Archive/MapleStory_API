#include "UINotice.h"
#include "UIImage.h"
#include "../GameManager.h"
#include "../Scene/BossWillPase2.h"
#include "../Scene/SceneManager.h"
#include "UIText.h"

CUINotice::CUINotice()
{
}

CUINotice::~CUINotice()
{
}

bool CUINotice::Init()
{
	Resolution	RS = CGameManager::GetInst()->GetResolution();

	SetPos(RS.Width / 2.f - 262.f, 100.f);

	CUIImage* Notice = CreateWidget<CUIImage>("Notice");

	Notice->SetTexture("Notice", TEXT("Notice1_2.bmp"));

	Notice->SetTextureColorKey(255, 0, 255);

	Notice->SetZOrder(5);

	return true;
}

void CUINotice::Update(float DeltaTime)
{
	CUIWindow::Update(DeltaTime);
}

void CUINotice::Finsh()
{
	Destroy();
}
