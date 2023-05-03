#include "bTitleScene.h"
#include "bInput.h"
#include "bSceneManager.h"
#include "bResources.h"
#include "bLogo.h"
#include "bAnimation.h"
#include "bObject.h"
#include "bCamera.h"
#include "bText.h"
#include "bApplication.h"
#include "bSound.h"

extern b::Application application;

namespace b
{
	TitleScene::TitleScene()
		: titleBackground(nullptr)
		, logo(nullptr)
		, mPos(Vector2::Zero)
		, sPos(Vector2::Zero)
		, ePos(Vector2::Zero)
		, start(nullptr)
		, end(nullptr)
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
		Scene::Initialize();

		Sound* peglinmenu = Resources::Load<Sound>(L"peglinmenu", L"..\\Resources\\audio\\peglinmenu.wav");
		peglinmenu->Play(true);

		logo = object::Instantiate<Logo>(Vector2(100.0f, 180.0f), Vector2(7.0f, 7.0f), eLayerType::BG);
		
		titleBackground = Resources::Load<Image>(L"titleBackground", L"..\\Resources\\sprite\\Background\\TitleSceneBackground.bmp");
		sPos = Vector2(500.0f, 440.0f);

		start = object::Instantiate<Text>(Vector2(500.0f, 440.0f), eLayerType::UI);
		wchar_t str[50] = L"New Game";
		start->SetText(*str);
		start->SetIsChange(true);
		start->SetTextHeight(80);

		ePos = Vector2(500.0f, 600.0f);
		end = object::Instantiate<Text>(Vector2(500.0f, 600.0f), eLayerType::UI);
		wchar_t str2[50] = L"Exit Game";
		end->SetText(*str2);
		end->SetIsChange(true);
		end->SetTextHeight(80);
	}

	void TitleScene::Update()
	{
		mPos = Input::GetMousePos();
		
		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			if (mPos.x >= sPos.x - 150.0f && mPos.x <= sPos.x + 150.0f
				&& mPos.y >= sPos.y - 10.0f && mPos.y <= sPos.y + 90.0f)
			{
				Sound* title_to_map = Resources::Load<Sound>(L"title_to_map", L"..\\Resources\\audio\\title_to_map.wav");
				title_to_map->Play(false);
				SceneManager::LoadScene(eSceneType::Map);
			}
			if (mPos.x >= ePos.x - 150.0f && mPos.x <= ePos.x + 150.0f
				&& mPos.y >= ePos.y - 10.0f && mPos.y <= ePos.y + 90.0f)
			{
				
				HWND hWnd = application.GetHwnd();
				SendMessage(hWnd, WM_CLOSE, 0, 0);
			}
		}
		
		Scene::Update();
	}

	void TitleScene::Render(HDC hdc)
	{
		StretchBlt(hdc, -1, -1, 1902, 1082, titleBackground->GetHdc(), 0, 0, titleBackground->GetWidth(), titleBackground->GetHeight(), SRCCOPY);

		Scene::Render(hdc);
	}

	void TitleScene::Release()
	{

		Scene::Release();
	}

	void TitleScene::OnEnter()
	{
		//Camera::StartFadeIn();
	}

	void TitleScene::OnExit()
	{
		//Camera::StartFadeOut();

		Sound* peglinmenu = Resources::Load<Sound>(L"peglinmenu", L"..\\Resources\\audio\\peglinmenu.wav");
		peglinmenu->Stop(true);
	}
}