#include "bEndingScene.h"
#include "bResources.h"
#include "bInput.h"
#include "bSceneManager.h"

namespace b
{
	EndingScene::EndingScene()
		: endScreen(nullptr)
	{
	}

	EndingScene::~EndingScene()
	{
	}

	void EndingScene::Initialize()
	{
		Scene::Initialize();
		
		endScreen = Resources::Load<Image>(L"endScreen", L"..\\Resources\\sprite\\Background\\endscreen2.bmp");

	}

	void EndingScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::O) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Fight);
		}

		if (Input::GetKeyState(eKeyCode::P) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Title);
		}

		Scene::Update();
	}

	void EndingScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		StretchBlt(hdc, 0, 0
			, 1600
			, 900
			, endScreen->GetHdc(), 0, 0
			, endScreen->GetWidth(), endScreen->GetHeight(), SRCCOPY);
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