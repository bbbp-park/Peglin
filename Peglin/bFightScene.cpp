#include "bFightScene.h"
#include "bResources.h"
#include "bInput.h"
#include "bSceneManager.h"
#include "bPeglin.h"
#include "bMonster.h"
#include "bHPbar.h"
#include "bCollisionManager.h"
#include "bObject.h"
#include "bCamera.h"
#include "bSpeedUp.h"
#include "bBag.h"

namespace b
{
	FightScene::FightScene()
		: mPeglin(nullptr)
		, mHPbar(nullptr)
		, forest1_bg(nullptr)
		, forest1_tile(nullptr)
	{
	}

	FightScene::~FightScene()
	{
	}

	void FightScene::Initialize()
	{

		Scene::Initialize();

		object::Instantiate<Peglin>(Vector2(430.0f, -280.0f), Vector2(3.0f, 3.0f), eLayerType::Player);

		object::Instantiate<Monster>(Vector2(800.0f, -250.0f), Vector2(3.0f, 3.0f), eLayerType::Monster);

		object::Instantiate<HPbar>(eLayerType::UI);
		object::Instantiate<Bag>(Vector2(140.0f, 0.0f), Vector2(2.4f, 2.4f), eLayerType::UI);
		object::Instantiate<SpeedUp>(eLayerType::UI);

		forest1_bg = Resources::Load<Image>(L"forest1_bg", L"..\\Resources\\sprite\\Background\\forest_1_background.bmp");
		forest1_tile = Resources::Load<Image>(L"forest1_tile", L"..\\Resources\\sprite\\Background\\forest_1_tile.bmp");
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

		for (size_t i = 0; i < 35; i++)
		{
			int x = forest1_tile->GetWidth() * 3 * i;
			StretchBlt(hdc, x, 220
				, forest1_tile->GetWidth() * 3
				, forest1_tile->GetHeight() * 3
				, forest1_tile->GetHdc(), 0, 0
				, forest1_tile->GetWidth(), forest1_tile->GetHeight(), SRCCOPY);
		}

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
		Camera::StartFadeIn();
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
	}

	void FightScene::OnExit()
	{
	}
}