#include "bFightScene.h"
#include "bResources.h"
#include "bInput.h"
#include "bSceneManager.h"

namespace b
{
	FightScene::FightScene()
	{
	}

	FightScene::~FightScene()
	{
	}

	void FightScene::Initialize()
	{
		forest1_bg = Resources::Load<Image>(L"forest1_bg", L"..\\Resources\\sprite\\Background\\forest_1_background.bmp");
		forest1_tile = Resources::Load<Image>(L"forest1_tile", L"..\\Resources\\sprite\\Background\\forest_1_tile.bmp");

		Scene::Initialize();
	}

	void FightScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Fight);
		}

		if (Input::GetKeyState(eKeyCode::M) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Ending);
		}
	}

	void FightScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		StretchBlt(hdc, -178, -85
			, forest1_bg->GetWidth() * 3
			, forest1_bg->GetHeight() * 3
			, forest1_bg->GetHdc(), 0, 0
			, forest1_bg->GetWidth(), forest1_bg->GetHeight(), SRCCOPY);

		/*StretchBlt(hdc, -1, 300 - forest1_tile->GetHeight(), forest1_tile->GetWidth() * 3, forest1_tile->GetHeight() * 3, forest1_tile->GetHdc(), 0, 0, forest1_tile->GetWidth(), forest1_tile->GetHeight(), SRCCOPY);*/
	}

	void FightScene::Release()
	{
		Scene::Release();
	}

	void FightScene::OnEnter()
	{
	}

	void FightScene::OnExit()
	{
	}
}