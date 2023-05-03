#include "bEndingScene.h"
#include "bResources.h"
#include "bInput.h"
#include "bSceneManager.h"
#include "bObject.h"
#include "bText.h"

namespace b
{
	EndingScene::EndingScene()
		: endScreen(nullptr)
		, mText(nullptr)
	{
	}

	EndingScene::~EndingScene()
	{
	}

	void EndingScene::Initialize()
	{
		Scene::Initialize();
		
		endScreen = Resources::Load<Image>(L"endScreen", L"..\\Resources\\sprite\\Background\\endscreen2.bmp");

		mText = object::Instantiate<Text>(Vector2(800.0f, 100.0f), eLayerType::UI);
		wchar_t str[50] = L"½£ ¿Ï·á!";
		mText->SetText(*str);
		mText->SetIsChange(false);
		mText->SetTextHeight(80);
	}

	void EndingScene::Update()
	{
		Scene::Update();
		mText->SetTextHeight(80);
	}

	void EndingScene::Render(HDC hdc)
	{
		StretchBlt(hdc, 0, 0
			, 1600
			, 900
			, endScreen->GetHdc(), 0, 0
			, endScreen->GetWidth(), endScreen->GetHeight(), SRCCOPY);

		Scene::Render(hdc);
	}

	void EndingScene::Release()
	{
		Scene::Release();
	}

	void EndingScene::OnEnter()
	{
	}

	void EndingScene::OnExit()
	{
	}
}