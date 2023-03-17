#include "bFightScene.h"
#include "bResources.h"
#include "bInput.h"
#include "bSceneManager.h"
#include "bPeglin.h"
#include "bHPbar.h"

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
		mPeglin = new Peglin();
		AddGameObject(mPeglin, eLayerType::Player);

		mHPbar = new HPbar();
		AddGameObject(mHPbar, eLayerType::UI);

		forest1_bg = Resources::Load<Image>(L"forest1_bg", L"..\\Resources\\sprite\\Background\\forest_1_background.bmp");
		forest1_tile = Resources::Load<Image>(L"forest1_tile", L"..\\Resources\\sprite\\Background\\forest_1_tile.bmp");

		Scene::Initialize();
	}

	void FightScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::O) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Map);
		}

		if (Input::GetKeyState(eKeyCode::P) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Ending);
		}

		Scene::Update();
	}

	void FightScene::Render(HDC hdc)
	{
		HBRUSH brush = CreateSolidBrush(RGB(35, 31, 20));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

		StretchBlt(hdc, -178, -90
			, forest1_bg->GetWidth() * 3
			, forest1_bg->GetHeight() * 3
			, forest1_bg->GetHdc(), 0, 0
			, forest1_bg->GetWidth(), forest1_bg->GetHeight(), SRCCOPY);

		Scene::Render(hdc);

		DeleteObject(oldBrush);

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