#include "bTitleScene.h"
#include "bInput.h"
#include "bSceneManager.h"
#include "bResources.h"
#include "bLogo.h"
#include "bAnimation.h"
#include "bObject.h"
#include "bCamera.h"

namespace b
{
	TitleScene::TitleScene()
		: titleBackground(nullptr)
		, logo(nullptr)
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
		Scene::Initialize();

		logo = object::Instantiate<Logo>(Vector2(100.0f, 240.0f), Vector2(7.0f, 7.0f), eLayerType::BG);
		
		titleBackground = Resources::Load<Image>(L"titleBackground", L"..\\Resources\\sprite\\Background\\TitleSceneBackground.bmp");

		//font = AddFontResource(L"..\\Resources\\font\\Silver.ttf");
	}

	void TitleScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::P) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Map);
		}

		if (Input::GetKeyState(eKeyCode::O) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Ending);
		}

		Scene::Update();
	}

	void TitleScene::Render(HDC hdc)
	{
		StretchBlt(hdc, -1, -1, 1902, 1082, titleBackground->GetHdc(), 0, 0, titleBackground->GetWidth(), titleBackground->GetHeight(), SRCCOPY);

		//SetBkMode(hdc, 1);
		//SetTextColor(hdc, RGB(255, 255, 255));
		///*HFONT hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("..\\Resources\\font\\Silver.ttf"));
		//HFONT oldFont = (HFONT)SelectObject(hdc, hFont);*/
		//TextOut(hdc, 20, 20, L"´Ù¶÷Áã", strlen("´Ù¶÷Áã"));
		

		Scene::Render(hdc);
	}

	void TitleScene::Release()
	{
		Scene::Release();
	}

	void TitleScene::OnEnter()
	{
	}

	void TitleScene::OnExit()
	{
		
	}
}