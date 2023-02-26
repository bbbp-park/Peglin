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

		StretchBlt(hdc, -1, -1, 1602, 902, titleBackground->GetHdc(), 0, 0, titleBackground->getWidth(), titleBackground->getHeight(), SRCCOPY);
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