#include "bTitleScene.h"
#include "bInput.h"
#include "bSceneManager.h"
#include "bResources.h"
#include "bLogo.h"
#include "bAnimation.h"

namespace b
{
	TitleScene::TitleScene()
		: mHdc(nullptr)
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
		logo = new Logo();
		
		titleBackground = Resources::Load<Image>(L"titleBackground", L"..\\Resources\\sprite\\Background\\TitleSceneBackground.bmp");

		AddGameObject(logo, eLayerType::BG);

		Scene::Initialize();
	}

	void TitleScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::M) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Map);
		}

		Scene::Update();
	}

	void TitleScene::Render(HDC hdc)
	{
		StretchBlt(hdc, -1, -1, 1902, 1082, titleBackground->GetHdc(), 0, 0, titleBackground->GetWidth(), titleBackground->GetHeight(), SRCCOPY);

		mHdc = hdc;
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