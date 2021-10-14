#include "EditorScene.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../UI/UIStart.h"
#include "../Input.h"
#include "EditorDlg.h"
#include "../Map/TileMap.h"
#include "../Map/ScrollMap.h"
#include "../GameManager.h"

CEditorScene::CEditorScene() : m_Dlg(nullptr), m_Start(false), m_TileMap(nullptr), m_ScroolSpeed(500.f)
{
	CGameManager::GetInst()->SetEditorMode(true);
}

CEditorScene::~CEditorScene()
{
	CGameManager::GetInst()->SetEditorMode(false);
	SAFE_DELETE(m_Dlg);
}

bool CEditorScene::Init()
{
	CScene::Init();

	LoadSound();

	LoadAnimationSequence();

	RECT rc = { 0, 0, 1366, 768 };

	HWND hWnd = CGameManager::GetInst()->GetWindowHandle();

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	SetWindowPos(hWnd, HWND_TOPMOST, 1920, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE);

	ShowWindow(hWnd, SW_SHOW);

	UpdateWindow(hWnd);

	m_Start = false;

	m_Dlg = new CEditorDlg;

	m_Dlg->SetScene(this);
	m_Dlg->Init(IDD_DIALOG_EDITOR);

	//CUIStart* StartWindow = CreateUIWindow<CUIStart>("StartWindow");

	return true;
}

bool CEditorScene::Update(float DeltaTime)
{
	CScene::Update(DeltaTime);

	if (!m_Start)
	{
		m_Start = true;

		CInput::GetInst()->SetCallback<CEditorScene>("Editor", KeyState_Down, this, &CEditorScene::OnEditor);

		CInput::GetInst()->SetCallback<CEditorScene>("MoveUp", KeyState_Push, this, &CEditorScene::CameraMoveUp);
		CInput::GetInst()->SetCallback<CEditorScene>("MoveDown", KeyState_Push, this, &CEditorScene::CameraMoveDown);
		CInput::GetInst()->SetCallback<CEditorScene>("MoveLeft", KeyState_Push, this, &CEditorScene::CameraMoveLeft);
		CInput::GetInst()->SetCallback<CEditorScene>("MoveRight", KeyState_Push, this, &CEditorScene::CameraMoveRight);

		CInput::GetInst()->SetCallback<CEditorScene>("MouseLButton", KeyState_Push, this, &CEditorScene::MouseLButton);
		CInput::GetInst()->SetCallback<CEditorScene>("MouseRButton", KeyState_Push, this, &CEditorScene::MouseRButton);
	}

	RECT rc = m_Dlg->GetRect();

	POINT ptMouse;
	GetCursorPos(&ptMouse);

	if (rc.left <= ptMouse.x && ptMouse.x <= rc.right && rc.top <= ptMouse.y && ptMouse.y <= rc.bottom)
	{
		if (!CInput::GetInst()->IsShowCursor())
		{
			CInput::GetInst()->SetShowCursor(true);
			ShowCursor(TRUE);
		}
	}

	else
	{
		if (CInput::GetInst()->IsShowCursor())
		{
			CInput::GetInst()->SetShowCursor(false);
			ShowCursor(FALSE);
		}
	}

	return false;
}

bool CEditorScene::PostUpdate(float DeltaTime)
{
	CScene::PostUpdate(DeltaTime);

	return false;
}

void CEditorScene::LoadAnimationSequence()
{

}

void CEditorScene::LoadSound()
{
	GetSceneResource()->LoadSound("UI", false, "ButtonMouseOn", "TeemoSmile.mp3");
	GetSceneResource()->LoadSound("UI", false, "ButtonClick", "TeemoStartClicck.mp3");

	GetSceneResource()->SetVolume("UI", 30);
}

void CEditorScene::OnEditor(float DeltaTiem)
{

}

void CEditorScene::CreateTileMap()
{
	if (m_TileMap)
	{
		return;
	}

	m_TileMap = CreateMap<CTileMap>("TileMap");
}

void CEditorScene::SetTileInfo(int CountX, int CountY, int SizeX, int SizeY)
{
	m_TileMap->CreateTile(CountX, CountY, Vector2((float)SizeX, (float)SizeY));
}

void CEditorScene::SetTileTexture(CTexture* Texture)
{
	m_TileMap->SetTileTexture(Texture);
}

void CEditorScene::CreateBack()
{
	if (m_ScrolMap)
	{
		return;
	}

	m_ScrolMap = CreateMap<CScrollMap>("ScrollMap");
}

void CEditorScene::SetBackInfo(int SizeX, int SizeY)
{
	m_ScrolMap->SetSize((float)SizeX, (float)SizeY);
}

void CEditorScene::SetBackTexture(std::string MapName, std::string TextureName)
{
	TCHAR str[256] = L"";

	size_t Size = 0;
	size_t conSize = 0;

	Size = strlen(TextureName.c_str()) + 1;

	mbstowcs_s(&conSize, str, Size, TextureName.c_str(), _TRUNCATE);

	m_ScrolMap->SetTexture(MapName, str);
}

void CEditorScene::CameraMoveUp(float DeltaTime)
{
	CCamera* Camera = GetCamera();

	Camera->Move(Vector2(0.f, -1.f) * m_ScroolSpeed * DeltaTime);
}

void CEditorScene::CameraMoveDown(float DeltaTime)
{
	CCamera* Camera = GetCamera();

	Camera->Move(Vector2(0.f, 1.f) * m_ScroolSpeed * DeltaTime);
}

void CEditorScene::CameraMoveLeft(float DeltaTime)
{
	CCamera* Camera = GetCamera();

	Camera->Move(Vector2(-1.f, 0.f) * m_ScroolSpeed * DeltaTime);
}

void CEditorScene::CameraMoveRight(float DeltaTime)
{
	CCamera* Camera = GetCamera();

	Camera->Move(Vector2(1.f, 0.f) * m_ScroolSpeed * DeltaTime);
}

void CEditorScene::MouseLButton(float DeltaTime)
{
	if (!m_TileMap)
	{
		return;
	}

	Vector2 MousePos = CInput::GetInst()->GetMousePos();

	CCamera* Camera = GetCamera();

	if (MousePos.x < 0.f || MousePos.x > Camera->GetResolution().x || MousePos.y < 0.f || MousePos.y > Camera->GetResolution().y)
	{
		return;
	}

	ETileEditMode EditMode = m_Dlg->GetTileEditMode();

	MousePos += Camera->GetPos();

	switch (EditMode)
	{
	case ETileEditMode::Option:
	{
		ETileOption Option = m_Dlg->GetTileOption();

		m_TileMap->ChangeTileOption(MousePos, Option);

		m_TileMap->ChangeTileSideCollision(MousePos, m_Dlg->GetSideCollision());
	}
	break;

	case ETileEditMode::Image:
	{
		TileFrmaeData FrameData = m_Dlg->GetTileFrameData();

		m_TileMap->SetTileFrmae(MousePos, FrameData.Start, FrameData.End);
	}
	break;
	}
}

void CEditorScene::MouseRButton(float DeltaTime)
{
	if (!m_TileMap)
	{
		return;
	}

	Vector2 MousePos = CInput::GetInst()->GetMousePos();

	CCamera* Camera = GetCamera();

	if (MousePos.x < 0.f || MousePos.x > Camera->GetResolution().x || MousePos.y < 0.f || MousePos.y > Camera->GetResolution().y)
	{
		return;
	}

	ETileEditMode EditMode = m_Dlg->GetTileEditMode();

	MousePos += Camera->GetPos();

	switch (EditMode)
	{
	case ETileEditMode::Option:
	{
		m_TileMap->ChangeTileOption(MousePos, ETileOption::Normal);
	}
	break;
	case ETileEditMode::Image:
	{
		m_TileMap->SetTileTexture(MousePos, nullptr);
	}
	break;
	}
}

void CEditorScene::Save(const char* FullPath)
{
	if (!m_TileMap)
	{
		MessageBox(0, TEXT("맵을 생성하세요"), TEXT("Error"), MB_OK);
		return;
	}

	m_TileMap->SaveFullPath(FullPath);
}

void CEditorScene::Load(const char* FullPath)
{
	if (!m_TileMap)
	{
		m_TileMap = CreateMap<CTileMap>("TileMap");
	}

	m_TileMap->LoadFullPath(FullPath);
}

void CEditorScene::TileImageAllClear()
{
	if (!m_TileMap)
	{
		return;
	}

	m_TileMap->TileImageAllClear();
}
