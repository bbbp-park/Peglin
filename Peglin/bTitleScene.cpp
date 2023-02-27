#include "bTitleScene.h"
#include "bInput.h"
#include "bSceneManager.h"
#include "bResources.h"

namespace b
{
	TitleScene::TitleScene()
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
		titleBackground = Resources::Load<Image>(L"titleBackground", L"..\\Resources\\sprite.bmp\\TitleSceneBackground.bmp");
		logo = Resources::Load<Image>(L"Logo", L"..\\Resources\\sprite.bmp\\titleLogo.bmp");
	}

	void TitleScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Play);
		}
	}

	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		StretchBlt(hdc, -1, -1, 1902, 1082, titleBackground->GetHdc(), 0, 0, titleBackground->getWidth(), titleBackground->getHeight(), SRCCOPY);
		StretchBlt(hdc, -1, -1, logo->getWidth(), logo->getHeight(), logo->GetHdc(), 0, 0, logo->getWidth(), logo->getHeight(), SRCCOPY);
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