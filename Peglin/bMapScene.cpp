#include "bMapScene.h"
#include "bMapPeglin.h"
#include "bInput.h"
#include "bSceneManager.h"
#include "bResources.h"
#include "bSpeedUp.h"
#include "bAnimation.h"
#include "bTime.h"

namespace b
{
	MapScene::MapScene()
	{
	}

	MapScene::~MapScene()
	{
	}

	void MapScene::Initialize()
	{
		mMapPeglin = new MapPeglin();
		AddGameObject(mMapPeglin, eLayerType::Player);

		treeTop = Resources::Load<Image>(L"treeTop", L"..\\Resources\\sprite\\Background\\treetop_.bmp");

		mSpeedUp = new SpeedUp();
		AddGameObject(mSpeedUp, eLayerType::UI);

		Scene::Initialize();
	}

	void MapScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::O) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Title);
		}

		if (Input::GetKeyState(eKeyCode::P) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Fight);
		}

		if (Input::GetKeyState(eKeyCode::F) == eKeyState::Down)
		{
			if (mSpeedUp->GetIndicator())
				mSpeedUp->SetIndicator(false);
			else
				mSpeedUp->SetIndicator(true);
		}

		Scene::Update();
	}

	void MapScene::Render(HDC hdc)
	{
		HBRUSH brush = CreateSolidBrush(RGB(48, 130, 48));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

		TransparentBlt(hdc, -990, -405
			, treeTop->GetWidth() * 2.4
			, treeTop->GetHeight() * 2.4
			, treeTop->GetHdc(), 0, 0
			, treeTop->GetWidth()
			, treeTop->GetHeight()
			, RGB(255, 0, 255));
		
		Scene::Render(hdc);
		DeleteObject(oldBrush);
	}

	void MapScene::Release()
	{
		Scene::Release();
	}

	void MapScene::OnEnter()
	{

	}

	void MapScene::OnExit()
	{
	}
}